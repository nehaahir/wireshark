/* packet-rip.c
 * Routines for RIPv1 and RIPv2 packet disassembly
 * RFC1058 (STD 34), RFC1388, RFC1723, RFC2453 (STD 56)
 * (c) Copyright Hannes R. Boehm <hannes@boehm.org>
 *
 * RFC2082 ( Keyed Message Digest Algorithm )
 *   Emanuele Caratti  <wiz@iol.it>
 *
 * $Id: packet-rip.c 53175 2013-11-08 21:38:32Z darkjames $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#define NEW_PROTO_TREE_API

#include "config.h"

#include <glib.h>
#include <epan/packet.h>
#include <epan/emem.h>
#include <epan/prefs.h>

#define UDP_PORT_RIP    520

#define	RIPv1	1
#define	RIPv2	2

static const value_string version_vals[] = {
	{ RIPv1, "RIPv1" },
	{ RIPv2, "RIPv2" },
	{ 0,     NULL }
};

static const value_string command_vals[] = {
	{ 1, "Request" },
	{ 2, "Response" },
	{ 3, "Traceon" },
	{ 4, "Traceoff" },
	{ 5, "Vendor specific (Sun)" },
	{ 0, NULL }
};

#define AFVAL_UNSPEC	0
#define AFVAL_IP	2

static const value_string family_vals[] = {
	{ AFVAL_UNSPEC,	"Unspecified" },
	{ AFVAL_IP,	"IP" },
	{ 0,		NULL }
};

#define AUTH_IP_ROUTE		1
#define AUTH_PASSWORD		2
#define AUTH_KEYED_MSG_DIGEST	3

static const value_string rip_auth_type[] = {
	{ AUTH_IP_ROUTE,		"IP Route" },
	{ AUTH_PASSWORD,		"Simple Password" },
	{ AUTH_KEYED_MSG_DIGEST,	"Keyed Message Digest" },
	{ 0,				NULL }
};

#define RIP_HEADER_LENGTH 4
#define RIP_ENTRY_LENGTH 20
#define MD5_AUTH_DATA_LEN 16

static gboolean pref_display_routing_domain = FALSE;

void proto_reg_handoff_rip(void);


static dissector_handle_t rip_handle;

static header_field_info *hfi_rip = NULL;

#define RIP_HFI_INIT HFI_INIT(proto_rip)

static header_field_info hfi_rip_command RIP_HFI_INIT =
	{ "Command", "rip.command", FT_UINT8, BASE_DEC,
	  VALS(command_vals), 0, "What type of RIP Command is this", HFILL };

static header_field_info hfi_rip_version RIP_HFI_INIT =
	{ "Version", "rip.version", FT_UINT8, BASE_DEC,
	  VALS(version_vals), 0, "Version of the RIP protocol", HFILL };

static header_field_info hfi_rip_routing_domain RIP_HFI_INIT =
	{ "Routing Domain", "rip.routing_domain", FT_UINT16, BASE_DEC,
	  NULL, 0, "RIPv2 Routing Domain", HFILL };

static header_field_info hfi_rip_ip RIP_HFI_INIT =
	{ "IP Address", "rip.ip", FT_IPv4, BASE_NONE,
	  NULL, 0, NULL, HFILL};

static header_field_info hfi_rip_netmask RIP_HFI_INIT =
	{ "Netmask", "rip.netmask", FT_IPv4, BASE_NONE,
	  NULL, 0, NULL, HFILL};

static header_field_info hfi_rip_next_hop RIP_HFI_INIT =
	{ "Next Hop", "rip.next_hop", FT_IPv4, BASE_NONE,
	  NULL, 0, "Next Hop router for this route", HFILL};

static header_field_info hfi_rip_metric RIP_HFI_INIT =
	{ "Metric", "rip.metric", FT_UINT16, BASE_DEC,
	  NULL, 0, "Metric for this route", HFILL };

static header_field_info hfi_rip_auth RIP_HFI_INIT =
	{ "Authentication type", "rip.auth.type", FT_UINT16, BASE_DEC,
	  VALS(rip_auth_type), 0, "Type of authentication", HFILL };

static header_field_info hfi_rip_auth_passwd RIP_HFI_INIT =
	{ "Password", "rip.auth.passwd", FT_STRING, BASE_NONE,
	  NULL, 0, "Authentication password", HFILL };

static header_field_info hfi_rip_family RIP_HFI_INIT =
	{ "Address Family", "rip.family", FT_UINT16, BASE_DEC,
	  VALS(family_vals), 0, NULL, HFILL };

static header_field_info hfi_rip_route_tag RIP_HFI_INIT =
	{ "Route Tag", "rip.route_tag", FT_UINT16, BASE_DEC,
	  NULL, 0, NULL, HFILL };

static gint ett_rip = -1;
static gint ett_rip_vec = -1;
static gint ett_auth_vec = -1;

static void dissect_unspec_rip_vektor(tvbuff_t *tvb, int offset, guint8 version,
    proto_tree *tree);
static void dissect_ip_rip_vektor(tvbuff_t *tvb, int offset, guint8 version,
    proto_tree *tree);
static gint dissect_rip_authentication(tvbuff_t *tvb, int offset,
    proto_tree *tree);

static void
dissect_rip(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    int offset = 0;
    proto_tree *rip_tree = NULL;
    proto_item *ti;
    guint8 command;
    guint8 version;
    guint16 family;
    gint trailer_len = 0;
    gboolean is_md5_auth = FALSE;

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "RIP");
    col_clear(pinfo->cinfo, COL_INFO);

    command = tvb_get_guint8(tvb, 0);
    version = tvb_get_guint8(tvb, 1);

    col_set_str(pinfo->cinfo, COL_PROTOCOL,
		    val_to_str_const(version, version_vals, "RIP"));
    col_add_str(pinfo->cinfo, COL_INFO,
		    val_to_str(command, command_vals, "Unknown command (%u)"));

    if (tree) {
	ti = proto_tree_add_item(tree, hfi_rip, tvb, 0, -1, ENC_NA);
	rip_tree = proto_item_add_subtree(ti, ett_rip);

	proto_tree_add_uint(rip_tree, &hfi_rip_command, tvb, 0, 1, command);
	proto_tree_add_uint(rip_tree, &hfi_rip_version, tvb, 1, 1, version);
	if (version == RIPv2 && pref_display_routing_domain == TRUE)
	    proto_tree_add_uint(rip_tree, &hfi_rip_routing_domain, tvb, 2, 2,
			tvb_get_ntohs(tvb, 2));

	/* skip header */
	offset = RIP_HEADER_LENGTH;

        /* zero or more entries */
	while (tvb_reported_length_remaining(tvb, offset) > trailer_len ) {
	    family = tvb_get_ntohs(tvb, offset);
	    switch (family) {
	    case AFVAL_UNSPEC: /* Unspecified */
	        /*
	         * There should be one entry in the request, and a metric
	         * of infinity, meaning "show the entire routing table".
	         */
		dissect_unspec_rip_vektor(tvb, offset, version, rip_tree);
		break;
	    case AFVAL_IP: /* IP */
		dissect_ip_rip_vektor(tvb, offset, version, rip_tree);
		break;
	    case 0xFFFF:
		if( offset == RIP_HEADER_LENGTH ) {
			trailer_len=dissect_rip_authentication(tvb, offset, rip_tree);
			is_md5_auth = TRUE;
		break;
		}
		if(is_md5_auth && tvb_reported_length_remaining(tvb, offset) == 20)
			break;
		/* Intentional fall through: auth Entry MUST be the first! */
	    default:
	        proto_tree_add_text(rip_tree, tvb, offset,
				RIP_ENTRY_LENGTH, "Unknown address family %u",
				family);
		break;
	    }

            offset += RIP_ENTRY_LENGTH;
        }
    }
}

static void
dissect_unspec_rip_vektor(tvbuff_t *tvb, int offset, guint8 version,
		      proto_tree *tree)
{
    proto_item *ti;
    proto_tree *rip_vektor_tree;
    guint32 metric;

    metric = tvb_get_ntohl(tvb, offset+16);
    ti = proto_tree_add_text(tree, tvb, offset,
			     RIP_ENTRY_LENGTH, "Address not specified, Metric: %u",
			     metric);
    rip_vektor_tree = proto_item_add_subtree(ti, ett_rip_vec);

    proto_tree_add_item(rip_vektor_tree, &hfi_rip_family, tvb, offset, 2, ENC_BIG_ENDIAN);
    if (version == RIPv2) {
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_route_tag, tvb, offset+2, 2,
			ENC_BIG_ENDIAN);
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_netmask, tvb, offset+8, 4,
			    ENC_BIG_ENDIAN);
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_next_hop, tvb, offset+12, 4,
			    ENC_BIG_ENDIAN);
    }
    proto_tree_add_uint(rip_vektor_tree, &hfi_rip_metric, tvb,
			offset+16, 4, metric);
}

static void
dissect_ip_rip_vektor(tvbuff_t *tvb, int offset, guint8 version,
		      proto_tree *tree)
{
    proto_item *ti;
    proto_tree *rip_vektor_tree;
    guint32 metric;

    metric = tvb_get_ntohl(tvb, offset+16);
    ti = proto_tree_add_text(tree, tvb, offset,
			     RIP_ENTRY_LENGTH, "IP Address: %s, Metric: %u",
			     tvb_ip_to_str(tvb, offset+4), metric);
    rip_vektor_tree = proto_item_add_subtree(ti, ett_rip_vec);

    proto_tree_add_item(rip_vektor_tree, &hfi_rip_family, tvb, offset, 2, ENC_BIG_ENDIAN);
    if (version == RIPv2) {
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_route_tag, tvb, offset+2, 2,
			ENC_BIG_ENDIAN);
    }

    proto_tree_add_item(rip_vektor_tree, &hfi_rip_ip, tvb, offset+4, 4, ENC_BIG_ENDIAN);

    if (version == RIPv2) {
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_netmask, tvb, offset+8, 4,
			    ENC_BIG_ENDIAN);
	proto_tree_add_item(rip_vektor_tree, &hfi_rip_next_hop, tvb, offset+12, 4,
			    ENC_BIG_ENDIAN);
    }
    proto_tree_add_uint(rip_vektor_tree, &hfi_rip_metric, tvb,
			offset+16, 4, metric);
}

static gint
dissect_rip_authentication(tvbuff_t *tvb, int offset, proto_tree *tree)
{
    proto_item *ti;
    proto_tree *rip_authentication_tree;
    guint16 authtype;
    guint32 val, digest_off, auth_data_len;

    auth_data_len = 0;
    authtype = tvb_get_ntohs(tvb, offset + 2);

    ti = proto_tree_add_text(tree, tvb, offset, RIP_ENTRY_LENGTH,
			"Authentication: %s", val_to_str( authtype, rip_auth_type, "Unknown (%u)" ) );
    rip_authentication_tree = proto_item_add_subtree(ti, ett_rip_vec);

    proto_tree_add_uint(rip_authentication_tree, &hfi_rip_auth, tvb, offset+2, 2,
		authtype);

    switch ( authtype ) {

    case AUTH_PASSWORD: /* Plain text password */
	proto_tree_add_item(rip_authentication_tree, &hfi_rip_auth_passwd,
			tvb, offset+4, 16, ENC_ASCII|ENC_NA);
	break;

    case AUTH_KEYED_MSG_DIGEST: /* Keyed MD5 rfc 2082 */
	digest_off = tvb_get_ntohs( tvb, offset+4 );
	proto_tree_add_text( rip_authentication_tree, tvb, offset+4, 2,
			"Digest Offset: %u" , digest_off );
	val = tvb_get_guint8( tvb, offset+6 );
	proto_tree_add_text( rip_authentication_tree, tvb, offset+6, 1,
			"Key ID: %u" , val );
	auth_data_len = tvb_get_guint8( tvb, offset+7 );
	proto_tree_add_text( rip_authentication_tree, tvb, offset+7, 1,
			"Auth Data Len: %u" , auth_data_len );
	val = tvb_get_ntohl( tvb, offset+8 );
	proto_tree_add_text( rip_authentication_tree, tvb, offset+8, 4,
			"Seq num: %u" , val );
	proto_tree_add_text( rip_authentication_tree, tvb, offset+12, 8,
			"Zero Padding" );
	ti = proto_tree_add_text( rip_authentication_tree, tvb, offset-4+digest_off,
			MD5_AUTH_DATA_LEN+4, "Authentication Data Trailer" );
	rip_authentication_tree = proto_item_add_subtree(ti, ett_auth_vec );
	proto_tree_add_text( rip_authentication_tree, tvb, offset-4+digest_off+4,
			MD5_AUTH_DATA_LEN, "Authentication Data: %s",
			tvb_bytes_to_str_punct(tvb, offset-4+digest_off+4,
					       MD5_AUTH_DATA_LEN, ' '));
	break;
    }
    return auth_data_len;
}

void
proto_register_rip(void)
{
#ifndef HAVE_HFI_SECTION_INIT
	static header_field_info *hfi[] = {
		&hfi_rip_command,
		&hfi_rip_version,
		&hfi_rip_family,
		&hfi_rip_routing_domain,
		&hfi_rip_ip,
		&hfi_rip_netmask,
		&hfi_rip_next_hop,
		&hfi_rip_metric,
		&hfi_rip_auth,
		&hfi_rip_auth_passwd,
		&hfi_rip_route_tag,
	};
#endif /* HAVE_HFI_SECTION_INIT */

	static gint *ett[] = {
		&ett_rip,
		&ett_rip_vec,
		&ett_auth_vec,
	};

	module_t *rip_module;
	int proto_rip;

	proto_rip = proto_register_protocol("Routing Information Protocol",
				"RIP", "rip");
	hfi_rip = proto_registrar_get_nth(proto_rip);

	proto_register_fields(proto_rip, hfi, array_length(hfi));
	proto_register_subtree_array(ett, array_length(ett));

	rip_module = prefs_register_protocol(proto_rip, proto_reg_handoff_rip);

	prefs_register_bool_preference(rip_module, "display_routing_domain", "Display Routing Domain field", "Display the third and forth bytes of the RIPv2 header as the Routing Domain field (introduced in RFC 1388 [January 1993] and obsolete as of RFC 1723 [November 1994])", &pref_display_routing_domain);

	rip_handle = create_dissector_handle(dissect_rip, proto_rip);
}

void
proto_reg_handoff_rip(void)
{
	dissector_add_uint("udp.port", UDP_PORT_RIP, rip_handle);
}
