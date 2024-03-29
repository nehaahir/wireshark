/* packet-sdp.c
 * Routines for SDP packet disassembly (RFC 2327)
 *
 * Jason Lango <jal@netapp.com>
 * Liberally copied from packet-http.c, by Guy Harris <guy@alum.mit.edu>
 *
 * $Id: packet-sdp.c 53288 2013-11-12 22:04:03Z mmann $
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
 * Ref http://www.ietf.org/rfc/rfc4566.txt?number=4566
 */

#include "config.h"

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#ifdef HAVE_WINSOCK2_H
#include <winsock2.h>           /* needed to define AF_ values on Windows */
#endif

#ifdef NEED_INET_V6DEFS_H
# include "wsutil/inet_v6defs.h"
#endif

#include <glib.h>

#include <epan/packet.h>
#include <epan/exceptions.h>
#include <epan/strutil.h>
#include <epan/wmem/wmem.h>
#include <epan/base64.h>
#include <epan/asn1.h>
#include <epan/prefs.h>
#include <epan/expert.h>
#include <epan/tap.h>
#include <epan/rtp_pt.h>
#include <epan/show_exception.h>

#include "packet-sdp.h"
#include "packet-rtp.h"

#include "packet-rtcp.h"
#include "packet-t38.h"
#include "packet-msrp.h"
#include "packet-sprt.h"
#include "packet-per.h"
#include "packet-h245.h"
#include "packet-h264.h"
#include "packet-mp4ves.h"

static dissector_handle_t rtcp_handle;
static dissector_handle_t sprt_handle;
static dissector_handle_t msrp_handle;
static dissector_handle_t h264_handle;
static dissector_handle_t mp4ves_handle;

static int sdp_tap = -1;

static int proto_sdp = -1;
static int proto_sprt = -1;

static const char* UNKNOWN_ENCODING = "Unknown";
static wmem_tree_t *sdp_transport_reqs = NULL;
static wmem_tree_t *sdp_transport_rsps = NULL;

/* preference globals */
static gboolean global_sdp_establish_conversation = TRUE;

/* Top level fields */
static int hf_protocol_version = -1;
static int hf_owner = -1;
static int hf_session_name = -1;
static int hf_session_info = -1;
static int hf_uri = -1;
static int hf_email = -1;
static int hf_phone = -1;
static int hf_connection_info = -1;
static int hf_bandwidth = -1;
static int hf_timezone = -1;
static int hf_encryption_key = -1;
static int hf_session_attribute = -1;
static int hf_media_attribute = -1;
static int hf_time = -1;
static int hf_repeat_time = -1;
static int hf_media = -1;
static int hf_media_title = -1;
static int hf_unknown = -1;
static int hf_invalid = -1;
static int hf_ipbcp_version = -1;
static int hf_ipbcp_type = -1;

/* hf_owner subfields*/
static int hf_owner_username = -1;
static int hf_owner_sessionid = -1;
static int hf_owner_version = -1;
static int hf_owner_network_type = -1;
static int hf_owner_address_type = -1;
static int hf_owner_address = -1;

/* hf_connection_info subfields */
static int hf_connection_info_network_type = -1;
static int hf_connection_info_address_type = -1;
static int hf_connection_info_connection_address = -1;
static int hf_connection_info_ttl = -1;
static int hf_connection_info_num_addr = -1;

/* hf_bandwidth subfields */
static int hf_bandwidth_modifier = -1;
static int hf_bandwidth_value = -1;

/* hf_time subfields */
static int hf_time_start = -1;
static int hf_time_stop = -1;

/* hf_repeat_time subfield */
static int hf_repeat_time_interval = -1;
static int hf_repeat_time_duration = -1;
static int hf_repeat_time_offset = -1;

/* hf_timezone subfields */
static int hf_timezone_time = -1;
static int hf_timezone_offset = -1;

/* hf_encryption_key subfields */
static int hf_encryption_key_type = -1;
static int hf_encryption_key_data = -1;

/* hf_session_attribute subfields */
static int hf_session_attribute_field = -1;
static int hf_session_attribute_value = -1;

/* hf_media subfields */
static int hf_media_media = -1;
static int hf_media_port = -1;
static int hf_media_portcount = -1;
static int hf_media_proto = -1;
static int hf_media_format = -1;

/* hf_session_attribute subfields */
static int hf_media_attribute_field = -1;
static int hf_media_attribute_value = -1;
static int hf_media_encoding_name = -1;
static int hf_media_sample_rate = -1;
static int hf_media_format_specific_parameter = -1;
static int hf_sdp_fmtp_mpeg4_profile_level_id = -1;
static int hf_sdp_fmtp_h263_profile = -1;
static int hf_sdp_fmtp_h263_level = -1;
static int hf_sdp_h264_packetization_mode = -1;
static int hf_SDPh223LogicalChannelParameters = -1;

/* hf_session_attribute hf_media_attribute subfields */
static int hf_key_mgmt_att_value = -1;
static int hf_key_mgmt_prtcl_id = -1;
static int hf_key_mgmt_data = -1;

static int hf_sdp_crypto_tag = -1;
static int hf_sdp_crypto_crypto_suite = -1;
static int hf_sdp_crypto_master_key = -1;
static int hf_sdp_crypto_master_salt = -1;
static int hf_sdp_crypto_lifetime = -1;
static int hf_sdp_crypto_mki = -1;
static int hf_sdp_crypto_mki_length = -1;

/* trees */
static int ett_sdp = -1;
static int ett_sdp_owner = -1;
static int ett_sdp_connection_info = -1;
static int ett_sdp_bandwidth = -1;
static int ett_sdp_time = -1;
static int ett_sdp_repeat_time = -1;
static int ett_sdp_timezone = -1;
static int ett_sdp_encryption_key = -1;
static int ett_sdp_session_attribute = -1;
static int ett_sdp_media = -1;
static int ett_sdp_media_attribute = -1;
static int ett_sdp_fmtp = -1;
static int ett_sdp_key_mgmt = -1;
static int ett_sdp_crypto_key_parameters = -1;

static expert_field ei_sdp_invalid_key_param = EI_INIT;
static expert_field ei_sdp_invalid_line = EI_INIT;

#define SDP_RTP_PROTO       0x00000001
#define SDP_SRTP_PROTO      0x00000002
#define SDP_T38_PROTO       0x00000004
#define SDP_MSRP_PROTO      0x00000008
#define SDP_SPRT_PROTO      0x00000010
#define SDP_IPv4            0x80000000
#define SDP_IPv6            0x40000000
#define SDP_MSRP_IPv4       0x20000000
#define SDP_VIDEO           0x10000000


#define SDP_MAX_RTP_CHANNELS 4
#define SDP_MAX_RTP_PAYLOAD_TYPES 20
#define SDP_NO_OF_PT 128
typedef struct {
  gint32 pt[SDP_MAX_RTP_PAYLOAD_TYPES];
  gint8 pt_count;
  GHashTable *rtp_dyn_payload;
  gboolean set_rtp;
} transport_media_pt_t;

typedef struct {
  enum sdp_exchange_type sdp_status;
  char  *encoding_name[SDP_NO_OF_PT];
  int    sample_rate[SDP_NO_OF_PT];
  int    media_port[SDP_MAX_RTP_CHANNELS];
  address  src_addr[SDP_MAX_RTP_CHANNELS];
  guint  proto_bitmask[SDP_MAX_RTP_CHANNELS];
  transport_media_pt_t media[SDP_MAX_RTP_CHANNELS];
  gint8  media_count;
  /* SRTP related info XXX note currently we only handle one crypto line in the SDP
   * We should probably handle offer/answer and session updates etc(SIP) quite possibly the whole handling of
   * seting up the RTP conversations should be done by the signaling protocol(s) calling the SDP dissector
   * and the SDP dissector just provide the relevant data.
   */
  guint  encryption_algorithm;
  guint  auth_algorithm;
  guint  mki_len;                /* number of octets used for the MKI in the RTP payload */
  guint  auth_tag_len;           /* number of octets used for the Auth Tag in the RTP payload */
} transport_info_t;

/* Data that is retrieved from a packet, but does not need to be kept */
typedef struct {
  char  *connection_address;
  char  *connection_type;
  char  *media_type;
  char  *media_port[SDP_MAX_RTP_CHANNELS];
  char  *media_proto[SDP_MAX_RTP_CHANNELS];
  guint8 media_count;

  /* MSRP transport info (as set while parsing path attribute) */
  gboolean msrp_transport_address_set;
  guint32  msrp_ipaddr[4];
  guint16  msrp_port_number;

} disposable_media_info_t;

/* key-mgmt dissector
 * IANA registry:
 * http://www.iana.org/assignments/sdp-parameters
 */
static dissector_table_t key_mgmt_dissector_table;

/* Subdissector functions */
static void
dissect_sdp_owner(tvbuff_t *tvb, proto_item *ti) {
  proto_tree *sdp_owner_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_owner_tree = proto_item_add_subtree(ti, ett_sdp_owner);

  /* Find the username */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_owner_tree, hf_owner_username, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);
  offset = next_offset  + 1;

  /* Find the session id */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_owner_tree, hf_owner_sessionid, tvb, offset,
                      tokenlen, ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the version */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_owner_tree, hf_owner_version, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the network type */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_owner_tree, hf_owner_network_type, tvb, offset,
                      tokenlen, ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the address type */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_owner_tree, hf_owner_address_type, tvb, offset,
                      tokenlen, ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the address */
  proto_tree_add_item(sdp_owner_tree, hf_owner_address, tvb, offset, -1, ENC_ASCII|ENC_NA);
}

/*
 * XXX - this can leak memory if an exception is thrown after we've fetched
 * a string.
 */
static void
dissect_sdp_connection_info(tvbuff_t *tvb, proto_item* ti,
                            disposable_media_info_t *media_info) {
  proto_tree *sdp_connection_info_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_connection_info_tree = proto_item_add_subtree(ti,
                                                    ett_sdp_connection_info);

  /* Find the network type */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_connection_info_tree,
                      hf_connection_info_network_type, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the address type */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;
  /* Save connection address type */
  media_info->connection_type = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);


  proto_tree_add_item(sdp_connection_info_tree,
                      hf_connection_info_address_type, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);
  offset = next_offset + 1;

  /* Find the connection address */
  /* XXX - what if there's a <number of addresses> value? */
  next_offset = tvb_find_guint8(tvb, offset, -1, '/');
  if (next_offset == -1) {
    tokenlen = -1; /* end of tvbuff */
    /* Save connection address */
    media_info->connection_address =
      (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tvb_length_remaining(tvb, offset));
  } else {
    tokenlen = next_offset - offset;
    /* Save connection address */
    media_info->connection_address = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
  }

  proto_tree_add_item(sdp_connection_info_tree,
                      hf_connection_info_connection_address, tvb, offset,
                      tokenlen, ENC_ASCII|ENC_NA);
  if (next_offset != -1) {
    offset = next_offset + 1;
    next_offset = tvb_find_guint8(tvb, offset, -1, '/');
    if (next_offset == -1) {
      tokenlen = -1; /* end of tvbuff */
    } else {
      tokenlen = next_offset - offset;
    }
    proto_tree_add_item(sdp_connection_info_tree,
                        hf_connection_info_ttl, tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
    if (next_offset != -1) {
      offset = next_offset + 1;
      proto_tree_add_item(sdp_connection_info_tree,
                          hf_connection_info_num_addr, tvb, offset, -1, ENC_ASCII|ENC_NA);
    }
  }
}

static void
dissect_sdp_bandwidth(tvbuff_t *tvb, proto_item *ti) {
  proto_tree *sdp_bandwidth_tree;
  gint        offset, next_offset, tokenlen;
  proto_item *item;
  gboolean    unit_is_kbs = FALSE;
  gboolean    unit_is_bps = FALSE;

  offset = 0;

  sdp_bandwidth_tree = proto_item_add_subtree(ti, ett_sdp_bandwidth);

  /* find the modifier */
  next_offset = tvb_find_guint8(tvb, offset, -1, ':');

  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;

  item = proto_tree_add_item(sdp_bandwidth_tree, hf_bandwidth_modifier, tvb, offset,
                             tokenlen, ENC_ASCII|ENC_NA);
  if (tvb_strneql(tvb, offset, "CT", 2) == 0) {
    proto_item_append_text(item, " [Conference Total(total bandwidth of all RTP sessions)]");
    unit_is_kbs = TRUE;
  } else if (tvb_strneql(tvb, offset, "AS", 2) == 0) {
    proto_item_append_text(item, " [Application Specific (RTP session bandwidth)]");
    unit_is_kbs = TRUE;
  } else if (tvb_strneql(tvb, offset, "TIAS", 4) == 0) {
    proto_item_append_text(item, " [Transport Independent Application Specific maximum]");
    unit_is_bps = TRUE;
  }


  offset = next_offset + 1;

  item = proto_tree_add_item(sdp_bandwidth_tree, hf_bandwidth_value, tvb, offset, -1,
                             ENC_ASCII|ENC_NA);
  if (unit_is_kbs == TRUE)
    proto_item_append_text(item, " kb/s");
  if (unit_is_bps == TRUE)
    proto_item_append_text(item, " b/s");
}

static void dissect_sdp_time(tvbuff_t *tvb, proto_item* ti) {
  proto_tree *sdp_time_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_time_tree = proto_item_add_subtree(ti, ett_sdp_time);

  /* get start time */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;
  proto_tree_add_item(sdp_time_tree, hf_time_start, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);

  /* get stop time */
  offset = next_offset + 1;
  proto_tree_add_item(sdp_time_tree, hf_time_stop, tvb, offset, -1, ENC_ASCII|ENC_NA);
}

static void dissect_sdp_repeat_time(tvbuff_t *tvb, proto_item* ti) {
  proto_tree *sdp_repeat_time_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_repeat_time_tree = proto_item_add_subtree(ti, ett_sdp_time);

  /* get interval */
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;
  proto_tree_add_item(sdp_repeat_time_tree, hf_repeat_time_interval, tvb,
                      offset, tokenlen, ENC_ASCII|ENC_NA);

  /* get duration */
  offset = next_offset + 1;
  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;
  proto_tree_add_item(sdp_repeat_time_tree, hf_repeat_time_duration, tvb,
                      offset, tokenlen, ENC_ASCII|ENC_NA);

  /* get offsets */
  do{
    offset = next_offset +1;
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
    if (next_offset != -1) {
      tokenlen = next_offset - offset;
    } else {
      tokenlen = -1; /* end of tvbuff */
    }
    proto_tree_add_item(sdp_repeat_time_tree, hf_repeat_time_offset,
                        tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
  } while (next_offset != -1);

}
static void
dissect_sdp_timezone(tvbuff_t *tvb, proto_item* ti) {
  proto_tree* sdp_timezone_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_timezone_tree = proto_item_add_subtree(ti, ett_sdp_timezone);

  do{
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
    if (next_offset == -1)
      break;
    tokenlen = next_offset - offset;

    proto_tree_add_item(sdp_timezone_tree, hf_timezone_time, tvb, offset,
                        tokenlen, ENC_ASCII|ENC_NA);
    offset = next_offset + 1;
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
    if (next_offset != -1) {
      tokenlen = next_offset - offset;
    } else {
      tokenlen = -1; /* end of tvbuff */
    }
    proto_tree_add_item(sdp_timezone_tree, hf_timezone_offset, tvb, offset,
                        tokenlen, ENC_ASCII|ENC_NA);
    offset = next_offset + 1;
  } while (next_offset != -1);

}


static void dissect_sdp_encryption_key(tvbuff_t *tvb, proto_item * ti) {
  proto_tree *sdp_encryption_key_tree;
  gint        offset, next_offset, tokenlen;

  offset = 0;

  sdp_encryption_key_tree = proto_item_add_subtree(ti, ett_sdp_encryption_key);

  next_offset = tvb_find_guint8(tvb, offset, -1, ':');

  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_encryption_key_tree, hf_encryption_key_type,
                      tvb, offset, tokenlen, ENC_ASCII|ENC_NA);

  offset = next_offset + 1;
  proto_tree_add_item(sdp_encryption_key_tree, hf_encryption_key_data,
                      tvb, offset, -1, ENC_ASCII|ENC_NA);
}

static void dissect_key_mgmt(tvbuff_t *tvb, packet_info * pinfo, proto_item * ti) {
  gchar      *data_p      = NULL;
  gchar      *prtcl_id    = NULL;
  gint        len;
  tvbuff_t   *keymgmt_tvb;
  gboolean    found_match = FALSE;
  proto_tree *key_tree;
  gint        next_offset;
  gint        offset      = 0;
  gint        tokenlen;

  key_tree = proto_item_add_subtree(ti, ett_sdp_key_mgmt);

  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;
  prtcl_id = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

  proto_tree_add_item(key_tree, hf_key_mgmt_prtcl_id, tvb, offset, tokenlen, ENC_ASCII|ENC_NA);

  offset = next_offset + 1;

  len = tvb_length_remaining(tvb, offset);
  if (len < 0)
    return;

  data_p = tvb_get_string(wmem_packet_scope(), tvb, offset, len);
  keymgmt_tvb = base64_to_tvb(tvb, data_p);
  add_new_data_source(pinfo, keymgmt_tvb, "Key Management Data");

  if ((prtcl_id != NULL) && (key_mgmt_dissector_table != NULL)) {
    found_match = dissector_try_string(key_mgmt_dissector_table,
                                       prtcl_id,
                                       keymgmt_tvb, pinfo,
                                       key_tree, NULL);
  }

  if (found_match) {
    proto_item *ti2 = proto_tree_add_item(key_tree, hf_key_mgmt_data,
                                          keymgmt_tvb, 0, -1, ENC_NA);
    PROTO_ITEM_SET_HIDDEN(ti2);
  } else {
    proto_tree_add_item(key_tree, hf_key_mgmt_data,
                        keymgmt_tvb, 0, -1, ENC_NA);
  }

}


static void dissect_sdp_session_attribute(tvbuff_t *tvb, packet_info * pinfo, proto_item * ti) {
  proto_tree *sdp_session_attribute_tree;
  gint        offset, next_offset, tokenlen;
  guint8     *field_name;

  offset = 0;

  sdp_session_attribute_tree = proto_item_add_subtree(ti,
                                                      ett_sdp_session_attribute);

  next_offset = tvb_find_guint8(tvb, offset, -1, ':');

  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;

  proto_tree_add_item(sdp_session_attribute_tree, hf_session_attribute_field,
                      tvb, offset, tokenlen, ENC_ASCII|ENC_NA);

  field_name = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

  offset = next_offset + 1;

  if (strcmp((char*)field_name, "ipbcp") == 0) {
    offset = tvb_pbrk_guint8(tvb, offset, -1,"0123456789", NULL);

    if (offset == -1)
      return;

    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

    if (next_offset == -1)
      return;

    tokenlen = next_offset - offset;

    proto_tree_add_item(sdp_session_attribute_tree, hf_ipbcp_version, tvb, offset, tokenlen, ENC_ASCII|ENC_NA);

    offset = tvb_pbrk_guint8(tvb, offset, -1,"ABCDEFGHIJKLMNOPQRSTUVWXYZ", NULL);

    if (offset == -1)
      return;

    tokenlen = tvb_find_line_end(tvb, offset, -1, &next_offset, FALSE);

    if (tokenlen == -1)
      return;

    proto_tree_add_item(sdp_session_attribute_tree, hf_ipbcp_type, tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
  } else if (strcmp((char*)field_name, "key-mgmt") == 0) {
    tvbuff_t   *key_tvb;
    proto_item *key_ti;

    key_tvb = tvb_new_subset_remaining(tvb, offset);
    key_ti = proto_tree_add_item(sdp_session_attribute_tree, hf_key_mgmt_att_value, key_tvb, 0, -1, ENC_ASCII|ENC_NA);

    dissect_key_mgmt(key_tvb, pinfo, key_ti);
  } else {
    proto_tree_add_item(sdp_session_attribute_tree, hf_session_attribute_value,
                        tvb, offset, -1, ENC_ASCII|ENC_NA);
  }
}


/* Dissect media description */
static void
dissect_sdp_media(tvbuff_t *tvb, proto_item *ti,
                  transport_info_t *transport_info, disposable_media_info_t *media_info) {
  proto_tree *sdp_media_tree;
  gint        offset, next_offset, tokenlen, idx;
  guint8     *media_format;

  offset = 0;

  /* Create tree for media session */
  sdp_media_tree = proto_item_add_subtree(ti, ett_sdp_media);

  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

  if (next_offset == -1)
    return;

  tokenlen = next_offset - offset;

  /* Type of media session */
  proto_tree_add_item(sdp_media_tree, hf_media_media, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);

  media_info->media_type = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

  offset = next_offset + 1;

  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
  if (next_offset == -1)
    return;
  tokenlen = next_offset - offset;
  next_offset = tvb_find_guint8(tvb, offset, tokenlen, '/');

  if (next_offset != -1) {
    tokenlen = next_offset - offset;
    /* Save port info */
    media_info->media_port[media_info->media_count] = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

    proto_tree_add_uint(sdp_media_tree, hf_media_port, tvb, offset, tokenlen,
                        atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen)));
    offset = next_offset + 1;
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
    if (next_offset == -1)
      return;
    tokenlen = next_offset - offset;
    proto_tree_add_item(sdp_media_tree, hf_media_portcount, tvb, offset,
                        tokenlen, ENC_ASCII|ENC_NA);
    offset = next_offset + 1;
  } else {
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

    if (next_offset == -1)
      return;
    tokenlen = next_offset - offset;
    /* Save port info */
    media_info->media_port[media_info->media_count] = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
    /* XXX Remember Port */
    proto_tree_add_uint(sdp_media_tree, hf_media_port, tvb, offset, tokenlen,
                        atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen)));
    offset = next_offset + 1;
  }

  next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

  if ( next_offset == -1)
    return;

  tokenlen = next_offset - offset;
  /* Save port protocol */
  media_info->media_proto[media_info->media_count] = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

  /* XXX Remember Protocol */
  proto_tree_add_item(sdp_media_tree, hf_media_proto, tvb, offset, tokenlen,
                      ENC_ASCII|ENC_NA);

  do {
    offset = next_offset + 1;
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

    if (next_offset == -1) {
      tokenlen = tvb_length_remaining(tvb, offset); /* End of tvbuff */
      if (tokenlen == 0)
        break; /* Nothing more left */
    } else {
      tokenlen = next_offset - offset;
    }

    if (!strcmp(media_info->media_proto[media_info->media_count], "RTP/AVP")) {
      media_format = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      proto_tree_add_string(sdp_media_tree, hf_media_format, tvb, offset,
                            tokenlen, val_to_str_ext((guint32)strtoul((char*)media_format, NULL, 10), &rtp_payload_type_vals_ext, "%u"));
      idx = transport_info->media[transport_info->media_count].pt_count;
      transport_info->media[transport_info->media_count].pt[idx] = (gint32)strtol((char*)media_format, NULL, 10);
      if (idx < (SDP_MAX_RTP_PAYLOAD_TYPES-1))
        transport_info->media[transport_info->media_count].pt_count++;
    } else {
      proto_tree_add_item(sdp_media_tree, hf_media_format, tvb, offset,
                          tokenlen, ENC_ASCII|ENC_NA);
    }
  } while (next_offset != -1);

  /* XXX Dissect traffic to "Port" as "Protocol"
   *     Remember this Port/Protocol pair so we can tear it down again later
   *     Actually, it's harder than that:
   *         We need to find out the address of the other side first and it
   *         looks like that info can be found in SIP headers only.
   */

}

static tvbuff_t *
ascii_bytes_to_tvb(tvbuff_t *tvb, packet_info *pinfo, gint len, gchar *msg)
{
  guint8 *buf = (guint8 *)wmem_alloc(pinfo->pool, 10240);

  /* arbitrary maximum length */
  if (len < 20480) {
    int i;
    tvbuff_t *bytes_tvb;

    /* first, skip to where the encoded pdu starts, this is
       the first hex digit after the '=' char.
    */
    while (1) {
      if ((*msg == 0) || (*msg == '\n')) {
        return NULL;
      }
      if (*msg == '=') {
        msg++;
        break;
      }
      msg++;
    }
    while (1) {
      if ((*msg == 0) || (*msg == '\n')) {
        return NULL;
      }
      if ( ((*msg >= '0') && (*msg <= '9'))
           || ((*msg >= 'a') && (*msg <= 'f'))
           || ((*msg >= 'A') && (*msg <= 'F'))) {
        break;
      }
      msg++;
    }
    i = 0;
    while (((*msg >= '0') && (*msg <= '9'))
           || ((*msg >= 'a') && (*msg <= 'f'))
           || ((*msg >= 'A') && (*msg <= 'F'))) {
      int val;
      if ((*msg >= '0') && (*msg <= '9')) {
        val = (*msg)-'0';
      } else if ((*msg >= 'a') && (*msg <= 'f')) {
        val = (*msg)-'a'+10;
      } else if ((*msg >= 'A') && (*msg <= 'F')) {
        val = (*msg)-'A'+10;
      } else {
        return NULL;
      }
      val <<= 4;
      msg++;
      if ((*msg >= '0') && (*msg <= '9')) {
        val |= (*msg)-'0';
      } else if ((*msg >= 'a') && (*msg <= 'f')) {
        val |= (*msg)-'a'+10;
      } else if ((*msg >= 'A') && (*msg <= 'F')) {
        val |= (*msg)-'A'+10;
      } else {
        return NULL;
      }
      msg++;

      buf[i] = (guint8)val;
      i++;
    }
    if (i == 0) {
      return NULL;
    }
    bytes_tvb = tvb_new_child_real_data(tvb, buf, i, i);
    add_new_data_source(pinfo, bytes_tvb, "ASCII bytes to tvb");
    return bytes_tvb;
  }
  return NULL;
}

/* Annex X Profiles and levels definition */
static const value_string h263_profile_vals[] =
{
  { 0,    "Baseline Profile" },
  { 1,    "H.320 Coding Efficiency Version 2 Backward-Compatibility Profile" },
  { 2,    "Version 1 Backward-Compatibility Profile" },
  { 3,    "Version 2 Interactive and Streaming Wireless Profile" },
  { 4,    "Version 3 Interactive and Streaming Wireless Profile" },
  { 5,    "Conversational High Compression Profile" },
  { 6,    "Conversational Internet Profile" },
  { 7,    "Conversational Interlace Profile" },
  { 8,    "High Latency Profile" },
  { 0, NULL },
};


/* RFC 4629 The level are described in table X.2 of H.263 annex X */
static const value_string h263_level_vals[] =
{
  { 10,    "QCIF (176 x 144), 1 x 64Kb/s" },
  { 20,    "CIF (352 x 288), 2 x 64Kb/s" },
  { 30,    "CIF (352 x 288), 6 x 64Kb/s" },
  { 40,    "CIF (352 x 288), 32 x 64Kb/s" },
  { 45,    "QCIF (176 x144) support of CPFMT, 2 x 64Kb/s" },
  { 50,    "CIF (352 x 288) support of CPFMT, 64 x 64Kb/s" },
  { 60,    "CPFMT: 720 x 288 support of CPFMT, 128 x 64Kb/s" },
  { 70,    "CPFMT: 720 x 576 support of CPFMT, 256 x 64Kb/s" },
  { 0, NULL },
};


static const value_string h264_packetization_mode_vals[] =
{
  { 0,    "Single NAL mode" },
  { 1,    "Non-interleaved mode" },
  { 2,    "Interleaved mode" },
  { 0, NULL },
};

/*
 * TODO: Make this a more generic routine to dissect fmtp parameters depending on media types
 */
static void
decode_sdp_fmtp(proto_tree *tree, tvbuff_t *tvb, packet_info *pinfo, gint offset, gint tokenlen, char *mime_type) {
  gint                 next_offset;
  gint                 end_offset;
  guint8              *field_name;
  gchar               *format_specific_parameter;
  proto_item          *item;
  tvbuff_t * volatile  data_tvb;

  end_offset = offset + tokenlen;

#if 0
    proto_tree_add_text(tree, tvb, offset, tokenlen, "Debug; Analysed string: '%s'",
    tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen));
#endif

  /* Look for an '=' within this value - this may indicate that there is a
     profile-level-id parameter to find if the MPEG4 media type is in use */
  next_offset = tvb_find_guint8(tvb, offset, -1, '=');
  if (next_offset == -1)
  {
    /* Give up (and avoid exception) if '=' not found */
    return;
  }

  /* Find the name of the parameter */
  tokenlen = next_offset - offset;
  field_name = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
#if 0
  proto_tree_add_text(tree, tvb, offset, tokenlen, "Debug; MIMEtype '%s'Parameter name: '%s'", mime_type, field_name); */
#endif
  offset = next_offset;

  /* Dissect the MPEG4 profile-level-id parameter if present */
  if ((mime_type != NULL) && (g_ascii_strcasecmp(mime_type, "MP4V-ES") == 0)) {
    if (strcmp((char*)field_name, "profile-level-id") == 0) {
      offset++;
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      item = proto_tree_add_uint(tree, hf_sdp_fmtp_mpeg4_profile_level_id, tvb, offset, tokenlen,
                                 (guint32)strtol((char*)format_specific_parameter, NULL, 10));
      PROTO_ITEM_SET_GENERATED(item);
    } else if (strcmp((char*)field_name, "config") == 0) {
      /* String including "=" */
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      /* ascii_bytes_to_tvb requires the "=" to be in the buffer */
      data_tvb = ascii_bytes_to_tvb(tvb, pinfo, tokenlen, format_specific_parameter);
      if (mp4ves_handle && data_tvb) {
        dissect_mp4ves_config(data_tvb, pinfo, tree);
      }
    }
  }

  /* Dissect the H263-2000 profile parameter if present */
  if (((mime_type != NULL) && (g_ascii_strcasecmp(mime_type, "H263-2000") == 0)) ||
      ((mime_type != NULL) && (g_ascii_strcasecmp(mime_type, "H263-1998") == 0))) {
    if (strcmp((char*)field_name, "profile") == 0) {
      offset++;
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      item = proto_tree_add_uint(tree, hf_sdp_fmtp_h263_profile, tvb, offset, tokenlen,
                                 (guint32)strtol((char*)format_specific_parameter, NULL, 10));
      PROTO_ITEM_SET_GENERATED(item);
    } else if (strcmp((char*)field_name, "level") == 0) {
      offset++;
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      item = proto_tree_add_uint(tree, hf_sdp_fmtp_h263_level, tvb, offset, tokenlen,
                                 (guint32)strtol((char*)format_specific_parameter, NULL, 10));
      PROTO_ITEM_SET_GENERATED(item);
    }
  }


  /* Dissect the H264 profile-level-id parameter
   * RFC 3984:
   * A base16 [6] (hexadecimal) representation of
   * the following three bytes in the sequence
   * parameter set NAL unit specified in [1]: 1)
   * profile_idc, 2) a byte herein referred to as
   * profile-iop, composed of the values of
   * constraint_set0_flag, constraint_set1_flag,
   * constraint_set2_flag, and reserved_zero_5bits
   * in bit-significance order, starting from the
   * most significant bit, and 3) level_idc.
   */
  if ((mime_type != NULL) && (g_ascii_strcasecmp(mime_type, "H264") == 0)) {
    if (strcmp(field_name, "profile-level-id") == 0) {
      int length = 0;

      /* Length includes "=" as it's required by ascii_bytes_to_tvb()*/
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      data_tvb = ascii_bytes_to_tvb(tvb, pinfo, tokenlen, format_specific_parameter);
      if (!data_tvb) {
        proto_tree_add_text(tree, tvb, offset, tokenlen, "Could not convert '%s' to 3 bytes", format_specific_parameter);
        return;
      }
      length = tvb_length(data_tvb);
      if (length == 3) {
        if (h264_handle && data_tvb) {
          dissect_h264_profile(data_tvb, pinfo, tree);
        }
      } else {
        item = proto_tree_add_text(tree, tvb, offset, tokenlen, "Incorrectly coded, must be three bytes");
        PROTO_ITEM_SET_GENERATED(item);
      }
    } else if (strcmp(field_name, "packetization-mode") == 0) {
      offset++;
      tokenlen = end_offset - offset;
      format_specific_parameter = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      item = proto_tree_add_uint(tree, hf_sdp_h264_packetization_mode, tvb, offset, tokenlen,
                                 (guint32)strtol((char*)format_specific_parameter, NULL, 10));
      PROTO_ITEM_SET_GENERATED(item);
    } else if (strcmp(field_name, "sprop-parameter-sets") == 0) {
      /* The value of the parameter is the
         base64 [6] representation of the initial
         parameter set NAL units as specified in
         sections 7.3.2.1 and 7.3.2.2 of [1].  The
         parameter sets are conveyed in decoding order,
         and no framing of the parameter set NAL units
         takes place.  A comma is used to separate any
         pair of parameter sets in the list.
      */
      gchar *data_p = NULL;
      gint   comma_offset;


      /* Move past '=' */
      offset++;
      comma_offset = tvb_find_guint8(tvb, offset, -1, ',');
      if (comma_offset != -1) {
        tokenlen = comma_offset - offset;
      } else {
        tokenlen = end_offset - offset;
      }

      data_p = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
      proto_tree_add_text(tree, tvb, offset, tokenlen, "NAL unit 1 string: %s", data_p);

      /* proto_tree_add_text(tree, tvb, offset, tokenlen, "String %s", data_p); */
      data_tvb = base64_to_tvb(tvb, data_p);
      add_new_data_source(pinfo, data_tvb, "h264 prop-parameter-sets");

      if (h264_handle && data_tvb) {
        TRY {
          dissect_h264_nal_unit(data_tvb, pinfo, tree);
        }
        CATCH_NONFATAL_ERRORS {
          show_exception(tvb, pinfo, tree, EXCEPT_CODE, GET_MESSAGE);
        }
        ENDTRY;
        if (comma_offset != -1) {
          /* Second NAL unit */
          offset   = comma_offset +1;
          tokenlen = end_offset - offset;
          data_p   = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
          proto_tree_add_text(tree, tvb, offset, tokenlen, "NAL unit 2 string: %s", data_p);
          data_tvb = base64_to_tvb(tvb, data_p);
          add_new_data_source(pinfo, data_tvb, "h264 prop-parameter-sets 2");
          dissect_h264_nal_unit(data_tvb, pinfo, tree);
        }
      }
    }
  }

}

typedef struct {
  const char *name;
} sdp_names_t;

#define SDP_RTPMAP              1
#define SDP_FMTP                2
#define SDP_PATH                3
#define SDP_H248_ITEM           4
#define SDP_CRYPTO              5
#define SDP_SPRTMAP             6

static const sdp_names_t sdp_media_attribute_names[] = {
  { "Unknown-name"},    /* 0 Pad so that the real headers start at index 1 */
  { "rtpmap"},          /* 1 */
  { "fmtp"},            /* 2 */
  { "path"},            /* 3 */
  { "h248item"},        /* 4 */
  { "crypto"},          /* 5 */
  { "sprt"},            /* 6 */
};

static gint find_sdp_media_attribute_names(tvbuff_t *tvb, int offset, guint len)
{
  guint i;

  for (i = 1; i < array_length(sdp_media_attribute_names); i++) {
    if ((len == strlen(sdp_media_attribute_names[i].name)) &&
        (tvb_strncaseeql(tvb, offset, sdp_media_attribute_names[i].name, len) == 0))
      return i;
  }

  return -1;
}

static void dissect_sdp_media_attribute(tvbuff_t *tvb, packet_info *pinfo, proto_item * ti, int length,
                                        transport_info_t *transport_info, disposable_media_info_t *media_info) {
  proto_tree *sdp_media_attribute_tree, *parameter_item;
  proto_item *fmtp_item, *media_format_item, *parameter_tree;
  proto_tree *fmtp_tree;
  gint        offset, next_offset, tokenlen, n, colon_offset;
  /*??guint8 *field_name;*/
  guint8     *payload_type;
  guint8     *attribute_value;
  gint       *key;
  guint8      pt;
  gint        sdp_media_attrbute_code;
  const char *msrp_res           = "msrp://";
  const char *h324ext_h223lcparm = "h324ext/h223lcparm";
  gboolean    has_more_pars      = TRUE;
  tvbuff_t   *h245_tvb;
  guint8      master_key_length  = 0, master_salt_length = 0;
  encoding_name_and_rate_t *encoding_name_and_rate;

  offset = 0;

  /* Create attribute tree */
  sdp_media_attribute_tree = proto_item_add_subtree(ti,
                                                    ett_sdp_media_attribute);
  /* Find end of field */
  colon_offset = tvb_find_guint8(tvb, offset, -1, ':');

  if (colon_offset == -1)
    return;

  /* Attribute field name is token before ':' */
  tokenlen = colon_offset - offset;
  proto_tree_add_item(sdp_media_attribute_tree,
                      hf_media_attribute_field,
                      tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
  /*??field_name = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);*/
  sdp_media_attrbute_code = find_sdp_media_attribute_names(tvb, offset, tokenlen);

  /* Skip colon */
  offset = colon_offset + 1;
  /* skip leading wsp */
  offset = tvb_skip_wsp(tvb, offset, tvb_length_remaining(tvb, offset));

  /* Value is the remainder of the line */
  attribute_value = tvb_get_string(wmem_packet_scope(), tvb, offset, tvb_length_remaining(tvb, offset));



  /*********************************************/
  /* Special parsing for some field name types */

  switch (sdp_media_attrbute_code) {
  case SDP_RTPMAP:
    /* decode the rtpmap to see if it is DynamicPayload to dissect them automatic */
    next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

    if (next_offset == -1)
      return;

    tokenlen = next_offset - offset;

    proto_tree_add_item(sdp_media_attribute_tree, hf_media_format, tvb,
                        offset, tokenlen, ENC_ASCII|ENC_NA);

    payload_type = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

    offset = next_offset + 1;

    next_offset = tvb_find_guint8(tvb, offset, -1, '/');

    if (next_offset == -1) {
      return;
    }

    tokenlen = next_offset - offset;

    proto_tree_add_item(sdp_media_attribute_tree, hf_media_encoding_name, tvb,
                        offset, tokenlen, ENC_ASCII|ENC_NA);

    pt = atoi((char*)payload_type);
    if (pt >= SDP_NO_OF_PT) {
      return;   /* Invalid */
    }

    key  = wmem_new(wmem_file_scope(), gint);
    *key = (gint)strtol((char*)payload_type, NULL, 10);

    transport_info->encoding_name[pt] = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);

    next_offset =  next_offset + 1;
    offset = next_offset;
    while (length-1 >= next_offset) {
      if (!g_ascii_isdigit(tvb_get_guint8(tvb, next_offset)))
        break;
      next_offset++;
    }
    tokenlen = next_offset - offset;
    proto_tree_add_item(sdp_media_attribute_tree, hf_media_sample_rate, tvb,
                        offset, tokenlen, ENC_ASCII|ENC_NA);
    transport_info->sample_rate[pt] = atoi(tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen));
    /* As per RFC2327 it is possible to have multiple Media Descriptions ("m=").
       For example:

       a=rtpmap:101 G726-32/8000
       m=audio 49170 RTP/AVP 0 97
       a=rtpmap:97 telephone-event/8000
       m=audio 49172 RTP/AVP 97 101
       a=rtpmap:97 G726-24/8000

       The Media attributes ("a="s) after the "m=" only apply for that "m=".
       If there is an "a=" before the first "m=", that attribute applies for
       all the session (all the "m="s).
    */

    /* so, if this "a=" appear before any "m=", we add it to all the dynamic
     * hash tables
     */
    if (transport_info->media_count < 0) {
      for (n = 0; n < SDP_MAX_RTP_CHANNELS; n++) {
        encoding_name_and_rate = wmem_new(wmem_file_scope(), encoding_name_and_rate_t);
        encoding_name_and_rate->encoding_name = wmem_strdup(wmem_file_scope(), transport_info->encoding_name[pt]);
        encoding_name_and_rate->sample_rate = transport_info->sample_rate[pt];
        if (n == 0) {
          g_hash_table_insert(transport_info->media[n].rtp_dyn_payload,
                              key, encoding_name_and_rate);
        } else {    /* we create a new key and encoding_name to assign to the other hash tables */
          gint *key2;
          key2  = wmem_new(wmem_file_scope(), gint);
          *key2 = (gint)strtol((char*)payload_type, NULL, 10);
          g_hash_table_insert(transport_info->media[n].rtp_dyn_payload,
                              key2, encoding_name_and_rate);
        }
      }
      return;
      /* if the "a=" is after an "m=", only apply to this "m=" */
    } else
      /* in case there is an overflow in SDP_MAX_RTP_CHANNELS, we keep always the last "m=" */
      encoding_name_and_rate = wmem_new(wmem_file_scope(), encoding_name_and_rate_t);

    encoding_name_and_rate->encoding_name = wmem_strdup(wmem_file_scope(), transport_info->encoding_name[pt]);
    encoding_name_and_rate->sample_rate   = transport_info->sample_rate[pt];
    g_hash_table_insert(transport_info->media[ transport_info->media_count ].rtp_dyn_payload,
                          key, encoding_name_and_rate);
    break;
  case SDP_FMTP:
    if (sdp_media_attribute_tree) {
      guint8 media_format;
      /* Reading the Format parameter(fmtp) */
      /* Skip leading space, if any */
      offset = tvb_skip_wsp(tvb, offset, tvb_length_remaining(tvb, offset));
      /* Media format extends to the next space */
      next_offset = tvb_find_guint8(tvb, offset, -1, ' ');

      if (next_offset == -1)
        return;

      tokenlen = next_offset - offset;


      media_format_item = proto_tree_add_item(sdp_media_attribute_tree,
                                              hf_media_format, tvb, offset,
                                              tokenlen, ENC_ASCII|ENC_NA);
      media_format = atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen));
      if (media_format >= SDP_NO_OF_PT) {
        return;   /* Invalid */
      }

      /* Append encoding name to format if known */
      proto_item_append_text(media_format_item, " [%s]",
                             transport_info->encoding_name[media_format]);

#if 0 /* XXX:  ?? */
      payload_type = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
#endif
      /* Move offset past the payload type */
      offset = next_offset + 1;

      while (has_more_pars == TRUE) {
        next_offset = tvb_find_guint8(tvb, offset, -1, ';');
        offset = tvb_skip_wsp(tvb, offset, tvb_length_remaining(tvb, offset));

        if (next_offset == -1) {
          has_more_pars = FALSE;
          next_offset= tvb_length(tvb);
        }

        /* There are at least 2 - add the first parameter */
        tokenlen = next_offset - offset;
        fmtp_item = proto_tree_add_item(sdp_media_attribute_tree,
                                        hf_media_format_specific_parameter, tvb,
                                        offset, tokenlen, ENC_ASCII|ENC_NA);

        fmtp_tree = proto_item_add_subtree(fmtp_item, ett_sdp_fmtp);

        decode_sdp_fmtp(fmtp_tree, tvb, pinfo, offset, tokenlen,
                        transport_info->encoding_name[media_format]);

        /* Move offset past "; " and onto firts char */
        offset = next_offset + 1;
      }
    }
    break;
  case SDP_PATH:
    /* msrp attributes that contain address needed for conversation */
    /*    RFC 4975
     *    path = path-label ":" path-list
     *    path-label = "path"
     *    path-list= MSRP-URI *(SP MSRP-URI)
     *    MSRP-URI = msrp-scheme "://" authority
     *       ["/" session-id] ";" transport *( ";" URI-parameter)
     *                        ; authority as defined in RFC3986
     *
     *    msrp-scheme = "msrp" / "msrps"
     * RFC 3986
     * The authority component is preceded by a double slash ("//") and is terminated by
     * the next slash ("/"), question mark ("?"), or number sign ("#") character, or by
     * the end of the URI.
     */

    /* Check for "msrp://" */
    if (strncmp((char*)attribute_value, msrp_res, strlen(msrp_res)) == 0) {
      int address_offset, port_offset, port_end_offset;

      /* Address starts here */
      address_offset = offset + (int)strlen(msrp_res);

      /* Port is after next ':' */
      port_offset = tvb_find_guint8(tvb, address_offset, -1, ':');
      /* Check if port is present if not skipp */
      if (port_offset!= -1) {
        /* Port ends with '/' */
        port_end_offset = tvb_find_guint8(tvb, port_offset, -1, '/');
        if (port_end_offset == -1) {
            /* No "/" look for the ";" */
            port_end_offset = tvb_find_guint8(tvb, port_offset, -1, ';');;
        }
        /* Attempt to convert address */
        if (inet_pton(AF_INET,
                      (char*)tvb_get_string(wmem_packet_scope(), tvb, address_offset, port_offset-address_offset),
                      &media_info->msrp_ipaddr) > 0) {
          /* Get port number */
          media_info->msrp_port_number = atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, port_offset + 1, port_end_offset - port_offset - 1));
          /* Set flag so this info can be used */
          media_info->msrp_transport_address_set = TRUE;
        }
      }
    }
    break;
  case SDP_H248_ITEM:
    /* Decode h248 item ITU-T Rec. H.248.12 (2001)/Amd.1 (11/2002)*/
    if (strncmp((char*)attribute_value, h324ext_h223lcparm, strlen(msrp_res)) == 0) {
      /* A.5.1.3 H.223 Logical channel parameters
       * This property indicates the H.245
       * H223LogicalChannelsParameters structure encoded by applying the PER specified in
       * ITU-T Rec. X.691. Value encoded as per A.5.1.2. For text encoding the mechanism defined
       * in ITU-T Rec. H.248.15 is used.
       */
      gint len;
      asn1_ctx_t actx;

      len = (gint)strlen(attribute_value);
      h245_tvb = ascii_bytes_to_tvb(tvb, pinfo, len, attribute_value);
      /* arbitrary maximum length */
      /* should go through a handle, however,  the two h245 entry
         points are different, one is over tpkt and the other is raw
      */
      if (h245_tvb) {
        asn1_ctx_init(&actx, ASN1_ENC_PER, TRUE, pinfo);
        dissect_h245_H223LogicalChannelParameters(h245_tvb, 0, &actx,
                                                  sdp_media_attribute_tree,
                                                  hf_SDPh223LogicalChannelParameters);
      }
    }
    break;
  case SDP_CRYPTO:
      /* http://tools.ietf.org/html/rfc4568
      * 9.1.  Generic "Crypto" Attribute Grammar
      *
      *   The ABNF grammar for the crypto attribute is defined below:
      *
      *   "a=crypto:" tag 1*WSP crypto-suite 1*WSP key-params
      *                                           *(1*WSP session-param)
      *
      *   tag              = 1*9DIGIT
      *   crypto-suite     = 1*(ALPHA / DIGIT / "_")
      *
      *   key-params       = key-param *(";" key-param)
      *   key-param        = key-method ":" key-info
      *   key-method       = "inline" / key-method-ext
      *   key-method-ext   = 1*(ALPHA / DIGIT / "_")
      *   key-info         = 1*(%x21-3A / %x3C-7E) ; visible (printing) chars
      *                                        ; except semi-colon
      *  session-param    = 1*(VCHAR)         ; visible (printing) characters
      *
      *   where WSP, ALPHA, DIGIT, and VCHAR are defined in [RFC4234].
      *
      */

      /* We are at the first colon */
      /* tag */
      next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
      if(next_offset==-1){
          /* XXX Add expert item? */
          return;
      }
      tokenlen    = next_offset - offset;
      proto_tree_add_uint(sdp_media_attribute_tree, hf_sdp_crypto_tag, tvb, offset, tokenlen,
          atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen)));
      offset = next_offset + 1;

      /* crypto-suite */
      next_offset = tvb_find_guint8(tvb, offset, -1, ' ');
      if(next_offset==-1){
          /* XXX Add expert item? */
          return;
      }
      tokenlen    = next_offset - offset;
      parameter_item = proto_tree_add_item(sdp_media_attribute_tree, hf_sdp_crypto_crypto_suite,
          tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
      if (tvb_strncaseeql(tvb, offset, "AES_CM_128_HMAC_SHA1_80", tokenlen) == 0) {

          /* XXX This may only work in simple cases */
          if (transport_info->encryption_algorithm == SRTP_ENC_ALG_NOT_SET) {
              transport_info->encryption_algorithm = SRTP_ENC_ALG_AES_CM;
              transport_info->auth_algorithm       = SRTP_AUTH_ALG_HMAC_SHA1;
              /* number of octets used for the Auth Tag in the RTP payload */
              transport_info->auth_tag_len         = 10;
          }
          master_key_length  = 16; /* 128 bits = 16 octets */
          master_salt_length = 14; /* 112 bits = 14 octets */
      } else if (tvb_strncaseeql(tvb, offset, "AES_CM_128_HMAC_SHA1_32", tokenlen) == 0) {
          /* XXX This may only work in simple cases */
          if (transport_info->encryption_algorithm == SRTP_ENC_ALG_NOT_SET) {
              transport_info->encryption_algorithm = SRTP_ENC_ALG_AES_CM;
              transport_info->auth_algorithm       = SRTP_AUTH_ALG_HMAC_SHA1;
              /* number of octets used for the Auth Tag in the RTP payload */
              transport_info->auth_tag_len         = 4;
          }
          master_key_length  = 16; /* 128 bits = 16 octets */
          master_salt_length = 14; /* 112 bits = 14 octets */
      } else if (tvb_strncaseeql(tvb, offset, "F8_128_HMAC_SHA1_80", tokenlen) == 0) {
          if (transport_info->encryption_algorithm == SRTP_ENC_ALG_NOT_SET) {
              /* XXX This may only work in simple cases */
              transport_info->encryption_algorithm = SRTP_ENC_ALG_AES_F8;
              transport_info->auth_algorithm       = SRTP_AUTH_ALG_HMAC_SHA1;
              /* number of octets used for the Auth Tag in the RTP payload */
              transport_info->auth_tag_len         = 10;
          }
          master_key_length  = 16; /* 128 bits = 16 octets */
          master_salt_length = 14; /* 112 bits = 14 octets */
      }
      offset = next_offset + 1;

      /* key-params */
      while (has_more_pars == TRUE) {
          int       param_end_offset;
          tvbuff_t *key_salt_tvb;
          gchar    *data_p = NULL;

          param_end_offset = tvb_find_guint8(tvb, offset, -1, ';');
          if (param_end_offset == -1) {
              has_more_pars = FALSE;
              param_end_offset = tvb_length(tvb);
          }
          /* key-method or key-method-ext */
          next_offset = tvb_find_guint8(tvb, offset, -1, ':');
          if (next_offset == -1) {
              expert_add_info(pinfo, parameter_item, &ei_sdp_invalid_key_param);
              break;
          }

          if (tvb_strncaseeql(tvb, offset, "inline", next_offset-offset) == 0) {
              parameter_item = proto_tree_add_text(sdp_media_attribute_tree,
                  tvb, offset, param_end_offset-offset, "Key parameters");
              parameter_tree = proto_item_add_subtree(parameter_item, ett_sdp_crypto_key_parameters);
              /* XXX only for SRTP? */
              /* srtp-key-info       = key-salt ["|" lifetime] ["|" mki] */
              offset      = next_offset +1;
              next_offset = tvb_find_guint8(tvb, offset, -1, '|');
              if (next_offset == -1) {
                  tokenlen = param_end_offset - offset;
              } else {
                  tokenlen = next_offset - offset;
              }
              data_p = tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen);
              key_salt_tvb = base64_to_tvb(tvb, data_p);
              add_new_data_source(pinfo, key_salt_tvb, "Key_Salt_tvb");
              if (master_key_length != 0) {
                  proto_tree_add_text(parameter_tree, tvb, offset, tokenlen, "Key and Salt");
                  proto_tree_add_item(parameter_tree, hf_sdp_crypto_master_key,
                      key_salt_tvb, 0, master_key_length, ENC_ASCII|ENC_NA);
                  proto_tree_add_item(parameter_tree, hf_sdp_crypto_master_salt,
                      key_salt_tvb, master_key_length, master_salt_length, ENC_ASCII|ENC_NA);
              } else {
                  proto_tree_add_text(parameter_tree, key_salt_tvb, 0, -1, "Key and Salt");
              }

              /*  ["|" lifetime] ["|" mki] are optional */
              if (next_offset != -1) {
                  offset = next_offset + 1;
                  next_offset = tvb_find_guint8(tvb, offset, -1, '|');
                  if(next_offset == -1){
                      if(next_offset < param_end_offset){
                          next_offset = param_end_offset;
                      }
                  }
                  if (next_offset != -1) {
                      /*lifetime           = ["2^"] 1*(DIGIT)   ; see section 6.1 for "2^" */
                      tokenlen = next_offset - offset;
                      proto_tree_add_item(parameter_tree, hf_sdp_crypto_lifetime,
                          tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
                      offset   = next_offset + 1;
                  }
                  /* mki                 = mki-value ":" mki-length
                  *
                  * mki-value           = 1*DIGIT
                  */
                  if(offset>param_end_offset){
                      next_offset = -1;
                  }else{
                      next_offset = tvb_find_guint8(tvb, offset, -1, ':');
                  }
                  if (next_offset != -1) {
                      tokenlen    = next_offset - offset;
                      proto_tree_add_item(parameter_tree, hf_sdp_crypto_mki, tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
                      offset      = next_offset + 1;

                      /* mki-length          = 1*3DIGIT   ; range 1..128. */
                      next_offset = param_end_offset;
                      tokenlen    = next_offset - offset;

                      /* This will not work if more than one parameter */
                      /* number of octets used for the MKI in the RTP payload */
                      transport_info->mki_len = atoi((char*)tvb_get_string(wmem_packet_scope(), tvb, offset, tokenlen));
                      proto_tree_add_item(parameter_tree, hf_sdp_crypto_mki_length,
                          tvb, offset, tokenlen, ENC_ASCII|ENC_NA);
                  }
              }
              offset = param_end_offset;
          } else {
              break;
          }
      }

    break;
  default:
    /* No special treatment for values of this attribute type, just add as one item. */
    proto_tree_add_item(sdp_media_attribute_tree, hf_media_attribute_value,
                        tvb, offset, -1, ENC_ASCII|ENC_NA);
    break;
  }
}

static void
call_sdp_subdissector(tvbuff_t *tvb, packet_info *pinfo, int hf, proto_tree* ti, int length,
                      transport_info_t *transport_info, disposable_media_info_t *media_info) {
  if (hf == hf_owner) {
    dissect_sdp_owner(tvb, ti);
  } else if (hf == hf_connection_info) {
    dissect_sdp_connection_info(tvb, ti, media_info);
  } else if (hf == hf_bandwidth) {
    dissect_sdp_bandwidth(tvb, ti);
  } else if (hf == hf_time) {
    dissect_sdp_time(tvb, ti);
  } else if (hf == hf_repeat_time) {
    dissect_sdp_repeat_time(tvb, ti);
  } else if (hf == hf_timezone) {
    dissect_sdp_timezone(tvb, ti);
  } else if (hf == hf_encryption_key) {
    dissect_sdp_encryption_key(tvb, ti);
  } else if (hf == hf_session_attribute) {
    dissect_sdp_session_attribute(tvb, pinfo, ti);
  } else if (hf == hf_media) {
    dissect_sdp_media(tvb, ti, transport_info, media_info);
  } else if (hf == hf_media_attribute) {
    dissect_sdp_media_attribute(tvb, pinfo, ti, length, transport_info, media_info);
  }
}

static void
convert_disposable_media(transport_info_t* transport_info, disposable_media_info_t* media_info,
                         gint start_transport_info_count)
{
  gint8 n, i, transport_index;
  guint proto_bitmask;

  for (n = 0; (n < media_info->media_count) && (n+start_transport_info_count < SDP_MAX_RTP_CHANNELS); n++)
  {
    transport_index = n+start_transport_info_count;
    if (media_info->media_port[n] != NULL) {
      transport_info->media_port[transport_index] = (int)strtol(media_info->media_port[n], NULL, 10);
    }

    if (media_info->media_proto[n] != NULL) {
      /* Check if media protocol is RTP
       * and stream decoding is enabled in preferences
       */
      if (global_sdp_establish_conversation) {
        proto_bitmask = 0;

        /* Check if media protocol is RTP */
        if (!strcmp(media_info->media_proto[n],"RTP/AVP")) {
          transport_info->proto_bitmask[transport_index] |= SDP_RTP_PROTO;
          proto_bitmask |= SDP_RTP_PROTO;
        }
        /* Check if media protocol is SRTP */
        else if (!strcmp(media_info->media_proto[n],"RTP/SAVP")) {
          transport_info->proto_bitmask[transport_index] |= SDP_SRTP_PROTO;
          proto_bitmask |= SDP_SRTP_PROTO;
        }
        /* Check if media protocol is T38 */
        else if ((!strcmp(media_info->media_proto[n],"UDPTL")) ||
            (!strcmp(media_info->media_proto[n],"udptl"))) {
          transport_info->proto_bitmask[transport_index] |= SDP_T38_PROTO;
          proto_bitmask |= SDP_T38_PROTO;
        }
        /* Check if media protocol is MSRP/TCP */
        else if (!strcmp(media_info->media_proto[n],"msrp/tcp")) {
          transport_info->proto_bitmask[transport_index] |= SDP_MSRP_PROTO;
          proto_bitmask |= SDP_MSRP_PROTO;
        }
        /* Check if media protocol is SPRT */
        else if ((!strcmp(media_info->media_proto[n],"UDPSPRT")) ||
            (!strcmp(media_info->media_proto[n],"udpsprt"))) {
          transport_info->proto_bitmask[transport_index] |= SDP_SPRT_PROTO;
          proto_bitmask |= SDP_SPRT_PROTO;
        }

        if (transport_info->media_port[transport_index] == 0) {
          /* This will disable any ports that share the media */
          for (i = 0; i < transport_index; i++) {
            if (proto_bitmask & transport_info->proto_bitmask[i]) {
               transport_info->media_port[i] = 0;
            }
          }
        }
      }
    }

    if ((media_info->connection_address != NULL) &&
        (media_info->connection_type != NULL)) {
      if (strcmp(media_info->connection_type, "IP4") == 0) {
        transport_info->src_addr[transport_index].data = wmem_alloc(wmem_file_scope(), 4);
        if (inet_pton(AF_INET, media_info->connection_address, (void*)transport_info->src_addr[transport_index].data) > 0) {
          /* connection_address could be converted to a valid ipv4 address*/
          transport_info->proto_bitmask[transport_index] |= SDP_IPv4;
          transport_info->src_addr[transport_index].type = AT_IPv4;
          transport_info->src_addr[transport_index].len  = 4;
        }
      } else if (strcmp(media_info->connection_type, "IP6") == 0) {
          transport_info->src_addr[transport_index].data = wmem_alloc(wmem_file_scope(), 16);
          if (inet_pton(AF_INET6, media_info->connection_address, (void*)transport_info->src_addr[transport_index].data) > 0) {
            /* connection_address could be converted to a valid ipv6 address*/
            transport_info->proto_bitmask[transport_index] |= SDP_IPv6;
            transport_info->src_addr[transport_index].type = AT_IPv6;
            transport_info->src_addr[transport_index].len  = 16;
          }
      }
    }

    /* MSRP uses addresses discovered in attribute
       rather than connection information of media session line */
    if ((transport_info->proto_bitmask[transport_index] & SDP_MSRP_PROTO) &&
        (transport_info->proto_bitmask[transport_index] & SDP_MSRP_IPv4) &&
        msrp_handle) {
       transport_info->src_addr[transport_index].type = AT_IPv4;
       transport_info->src_addr[transport_index].len  = 4;
       transport_info->src_addr[transport_index].data = wmem_memdup(wmem_file_scope(), media_info->msrp_ipaddr, 4);
       transport_info->media_port[transport_index] = media_info->msrp_port_number;
    }

    if ((media_info->media_type != NULL) && (strcmp(media_info->media_type, "video") == 0)) {
      transport_info->proto_bitmask[transport_index] |= SDP_VIDEO;
    }
  }
}

void
setup_sdp_transport(tvbuff_t *tvb, packet_info *pinfo, enum sdp_exchange_type exchange_type, int request_frame)
{
  gint        offset = 0, next_offset, n;
  int         linelen;
  gboolean    in_media_description = FALSE;
  guchar      type, delim;
  const int   tokenoffset = 2;
  int         hf     = -1;
  gint        start_transport_info_count = 0;
  transport_info_t* transport_info = NULL;
  disposable_media_info_t media_info;

  struct srtp_info *srtp_info = NULL;

  /* Only do this once during first pass */
  if (pinfo->fd->flags.visited)
     return;

  memset(&media_info, 0, sizeof(media_info));

  if (request_frame != 0)
    transport_info = (transport_info_t*)wmem_tree_lookup32( sdp_transport_reqs, request_frame );
  if (transport_info == NULL) {
    transport_info = wmem_new0(wmem_file_scope(), transport_info_t);
    transport_info->media_count = -1;

    for (n = 0; n < SDP_NO_OF_PT; n++) {
      transport_info->encoding_name[n] = (char*)UNKNOWN_ENCODING;
    }
    for (n = 0; n < SDP_MAX_RTP_CHANNELS; n++) {
      transport_info->media[n].rtp_dyn_payload =
          g_hash_table_new(g_int_hash, g_int_equal);
      transport_info->media[n].set_rtp = FALSE;
    }

    if (request_frame != 0)
      wmem_tree_insert32(sdp_transport_reqs, request_frame, (void *)transport_info);
  }

  if (exchange_type != SDP_EXCHANGE_OFFER)
    wmem_tree_insert32(sdp_transport_rsps, pinfo->fd->num, (void *)transport_info);

  /* Offer has already been answered or rejected and hash tables freed, so
   * don't try to add to it
   * XXX - Need to support "modified offers" */
  if ((transport_info->sdp_status == SDP_EXCHANGE_ANSWER_REJECT) ||
      (transport_info->sdp_status == SDP_EXCHANGE_ANSWER_ACCEPT))
      return;

  if (transport_info->media_count > 0)
    start_transport_info_count = transport_info->media_count;

  /*
   * Show the SDP message a line at a time.
   */
  while (tvb_reported_length_remaining(tvb, offset) > 0) {
    /*
     * Find the end of the line.
     */
    linelen = tvb_find_line_end_unquoted(tvb, offset, -1, &next_offset);

    /*
     * Line must contain at least e.g. "v=".
     */
    if (linelen < 2)
      break;

    type  = tvb_get_guint8(tvb, offset);
    delim = tvb_get_guint8(tvb, offset + 1);
    if (delim != '=') {
      offset = next_offset;
      continue;
    }

    /*
     * Attributes.  Only care about ones that affect the transport.  Ignore others.
     */
    switch (type) {
    case 'c':
      hf = hf_connection_info;
      break;
    case 'm':
      hf = hf_media;

      /* Increase the count of media channels, but don't walk off the end of the arrays. */
      if (((transport_info->media_count < 0) && (in_media_description == FALSE)) || (transport_info->media_count < (SDP_MAX_RTP_CHANNELS-1)))
        transport_info->media_count++;

      if (in_media_description && (media_info.media_count < (SDP_MAX_RTP_CHANNELS-1)))
        media_info.media_count++;

      in_media_description = TRUE;
      break;
    case 'a':
      if (in_media_description) {
        hf = hf_media_attribute;
      } else {
        hf = hf_session_attribute;
      }
      break;
    default:
      hf = hf_unknown;
      break;
    }

    if (hf != hf_unknown)
    {
      call_sdp_subdissector(tvb_new_subset(tvb, offset + tokenoffset,
                                             linelen - tokenoffset,
                                             linelen - tokenoffset),
                              pinfo,
                              hf, NULL, linelen-tokenoffset, transport_info, &media_info);
    }

    offset = next_offset;
  }

  if (in_media_description) {
    /* Increase the count of media channels, but don't walk off the end of the arrays. */
    if (transport_info->media_count < (SDP_MAX_RTP_CHANNELS-1))
      transport_info->media_count++;
    if (media_info.media_count < (SDP_MAX_RTP_CHANNELS-1))
      media_info.media_count++;
  }

  /* Take all of the collected strings and convert them into something permanent
   * for the life of the capture
   */
  convert_disposable_media(transport_info, &media_info, start_transport_info_count);

  /* We have a successful negotiation, apply data to their respective protocols */
  if ((exchange_type == SDP_EXCHANGE_ANSWER_ACCEPT) &&
      (transport_info->sdp_status == SDP_EXCHANGE_OFFER)) {
    for (n = 0; n <= transport_info->media_count; n++) {
      guint32 current_rtp_port = 0;

      /* Add (s)rtp and (s)rtcp conversation, if available (overrides t38 if conversation already set) */
      if ((transport_info->media_port[n] != 0) &&
          (transport_info->proto_bitmask[n] & (SDP_RTP_PROTO|SDP_SRTP_PROTO)) &&
          (transport_info->proto_bitmask[n] & (SDP_IPv4|SDP_IPv6))) {
        if (transport_info->proto_bitmask[n] & SDP_SRTP_PROTO) {
            srtp_info = wmem_new0(wmem_file_scope(), struct srtp_info);
            if (transport_info->encryption_algorithm != SRTP_ENC_ALG_NOT_SET) {
              srtp_info->encryption_algorithm = transport_info->encryption_algorithm;
              srtp_info->auth_algorithm       = transport_info->auth_algorithm;
              srtp_info->mki_len              = transport_info->mki_len;
              srtp_info->auth_tag_len         = transport_info->auth_tag_len;

            }
            srtp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num,
                            (transport_info->proto_bitmask[n] & SDP_VIDEO) ? TRUE : FALSE,
                             transport_info->media[n].rtp_dyn_payload, srtp_info);
        } else {
            rtp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num,
                            (transport_info->proto_bitmask[n] & SDP_VIDEO) ? TRUE : FALSE,
                            transport_info->media[n].rtp_dyn_payload);
        }
        transport_info->media[n].set_rtp = TRUE;
        /* SPRT might use the same port... */
        current_rtp_port = transport_info->media_port[n];

        if (rtcp_handle) {
          if (transport_info->proto_bitmask[n] & SDP_SRTP_PROTO) {
            srtcp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n]+1, 0, "SDP", pinfo->fd->num, srtp_info);
          } else {
            rtcp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n]+1, 0, "SDP", pinfo->fd->num);
          }
        }
      }

      /* add SPRT conversation */
      if ((transport_info->proto_bitmask[n] & SDP_SPRT_PROTO) &&
          (transport_info->proto_bitmask[n] & (SDP_IPv4|SDP_IPv6)) &&
          (sprt_handle)) {

        if (transport_info->media_port[n] == 0 && current_rtp_port) {
          sprt_add_address(pinfo, &transport_info->src_addr[n], current_rtp_port,
                           0, "SDP", pinfo->fd->num); /* will use same port as RTP */
        } else {
          sprt_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num);
        }
      }

      /* Add t38 conversation, if available and only if no rtp */
      if ((transport_info->media_port[n] != 0) &&
          !transport_info->media[n].set_rtp &&
          (transport_info->proto_bitmask[n] & SDP_T38_PROTO) &&
          (transport_info->proto_bitmask[n] & SDP_IPv4)) {
        t38_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num);
      }

      /* Add MSRP conversation.  Uses addresses discovered in attribute
         rather than connection information of media session line
         (already handled in media conversion) */
      if ((transport_info->proto_bitmask[n] & SDP_MSRP_PROTO) &&
          (transport_info->proto_bitmask[n] & SDP_MSRP_IPv4) &&
          msrp_handle) {
          msrp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], "SDP", pinfo->fd->num);
      }

      /* Free the hash table if we did't assigned it to a conv use it */
      if (!transport_info->media[n].set_rtp)
      {
          rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
          transport_info->media[n].rtp_dyn_payload = NULL;
      }
    }

    /* Free the remaining hash tables not used */
    if (transport_info->media_count == -1)
    {
      for (n = 0; n < SDP_MAX_RTP_CHANNELS; n++)
      {
        if (!transport_info->media[n].set_rtp)
        {
          rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
          transport_info->media[n].rtp_dyn_payload = NULL;
        }
      }
    }
    else
    {
      for (n = transport_info->media_count; n < SDP_MAX_RTP_CHANNELS; n++)
      {
        if (!transport_info->media[n].set_rtp)
        {
          rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
          transport_info->media[n].rtp_dyn_payload = NULL;
        }
      }
    }
    transport_info->sdp_status = SDP_EXCHANGE_ANSWER_ACCEPT;

  } else if ((exchange_type == SDP_EXCHANGE_ANSWER_REJECT) &&
             (transport_info->sdp_status != SDP_EXCHANGE_ANSWER_REJECT)){

    /* Free the hash tables, since they won't be put to use */
    for (n = 0; n < SDP_MAX_RTP_CHANNELS; n++)
    {
      if (!transport_info->media[n].set_rtp)
      {
        rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
        transport_info->media[n].rtp_dyn_payload = NULL;
      }
    }

    transport_info->sdp_status = SDP_EXCHANGE_ANSWER_REJECT;
  }
}

void setup_sdp_transport_resend(int current_frame, int request_frame)
{
  transport_info_t* transport_info = NULL;

  if (request_frame != 0) {
    transport_info = (transport_info_t*)wmem_tree_lookup32( sdp_transport_reqs, request_frame );
    if (transport_info != NULL) {
        wmem_tree_insert32(sdp_transport_reqs, current_frame, (void *)transport_info);
    }
  }
}

static void
dissect_sdp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
  proto_tree *sdp_tree;
  proto_item *ti, *sub_ti;
  gint        offset = 0, next_offset, n, i;
  int         linelen;
  gboolean    in_media_description;
  guchar      type, delim;
  int         datalen, tokenoffset, hf = -1;
  char       *string;

  transport_info_t  local_transport_info;
  transport_info_t* transport_info = NULL;
  disposable_media_info_t media_info;

  sdp_packet_info  *sdp_pi;
  struct srtp_info *srtp_info = NULL;

  /* Initialise packet info for passing to tap */
  sdp_pi = wmem_new(wmem_packet_scope(), sdp_packet_info);
  sdp_pi->summary_str[0] = '\0';

  if (!pinfo->fd->flags.visited) {
    transport_info = (transport_info_t*)wmem_tree_lookup32( sdp_transport_reqs, pinfo->fd->num );

    if (transport_info == NULL) {
       /* Can't find it in the requests, make sure it's not a response */
       transport_info = (transport_info_t*)wmem_tree_lookup32( sdp_transport_rsps, pinfo->fd->num );
    }
  }

  if (transport_info == NULL) {
    transport_info = &local_transport_info;
  }

  /* Initialize local transport info */
  memset(&local_transport_info, 0, sizeof(local_transport_info));
  local_transport_info.media_count = -1;

  for (n = 0; n < SDP_NO_OF_PT; n++) {
    local_transport_info.encoding_name[n] = (char*)UNKNOWN_ENCODING;
  }
  for (n = 0; n < SDP_MAX_RTP_CHANNELS; n++) {
    local_transport_info.media[n].rtp_dyn_payload =
        g_hash_table_new(g_int_hash, g_int_equal);
    local_transport_info.media[n].set_rtp = FALSE;
  }

  memset(&media_info, 0, sizeof(media_info));

  /*
   * As RFC 2327 says, "SDP is purely a format for session
   * description - it does not incorporate a transport protocol,
   * and is intended to use different transport protocols as
   * appropriate including the Session Announcement Protocol,
   * Session Initiation Protocol, Real-Time Streaming Protocol,
   * electronic mail using the MIME extensions, and the
   * Hypertext Transport Protocol."
   *
   * We therefore don't set the protocol or info columns;
   * instead, we append to them, so that we don't erase
   * what the protocol inside which the SDP stuff resides
   * put there.
   */
  col_append_str(pinfo->cinfo, COL_PROTOCOL, "/SDP");

  /* XXX: Needs description.
   * Putting with session description in info col is redundant when it's in the
   * protocol col in my opinion, commenting it out for now 2012-10-09. Remove if no one complains.
   * If some one want it consider " ,with SDP"
   */
  /*col_append_str(pinfo->cinfo, COL_INFO, ", with session description");*/

  ti = proto_tree_add_item(tree, proto_sdp, tvb, offset, -1, ENC_NA);
  sdp_tree = proto_item_add_subtree(ti, ett_sdp);

  /*
   * Show the SDP message a line at a time.
   */
  in_media_description = FALSE;

  while (tvb_reported_length_remaining(tvb, offset) > 0) {
    /*
     * Find the end of the line.
     */
    linelen = tvb_find_line_end_unquoted(tvb, offset, -1, &next_offset);

    /*
     * Line must contain at least e.g. "v=".
     */
    if (linelen < 2)
      break;

    type  = tvb_get_guint8(tvb, offset);
    delim = tvb_get_guint8(tvb, offset + 1);
    if (delim != '=') {
      proto_item *ti2 = proto_tree_add_item(sdp_tree, hf_invalid, tvb, offset, linelen, ENC_ASCII|ENC_NA);
      expert_add_info(pinfo, ti2, &ei_sdp_invalid_line);
      offset = next_offset;
      continue;
    }

    /*
     * Attributes.
     */
    switch (type) {
    case 'v':
      hf = hf_protocol_version;
      break;
    case 'o':
      hf = hf_owner;
      break;
    case 's':
      hf = hf_session_name;
      break;
    case 'i':
      if (in_media_description) {
        hf = hf_media_title;
      } else {
        hf = hf_session_info;
      }
      break;
    case 'u':
      hf = hf_uri;
      break;
    case 'e':
      hf = hf_email;
      break;
    case 'p':
      hf = hf_phone;
      break;
    case 'c':
      hf = hf_connection_info;
      break;
    case 'b':
      hf = hf_bandwidth;
      break;
    case 't':
      hf = hf_time;
      break;
    case 'r':
      hf = hf_repeat_time;
      break;
    case 'm':
      hf = hf_media;

      /* Increase the count of media channels, but don't walk off the end of the arrays. */
      if (local_transport_info.media_count < (SDP_MAX_RTP_CHANNELS-1))
        local_transport_info.media_count++;

      if (in_media_description && (media_info.media_count < (SDP_MAX_RTP_CHANNELS-1)))
        media_info.media_count++;

      in_media_description = TRUE;
      break;
    case 'k':
      hf = hf_encryption_key;
      break;
    case 'a':
      if (in_media_description) {
        hf = hf_media_attribute;
      } else {
        hf = hf_session_attribute;
      }
      break;
    case 'z':
      hf = hf_timezone;
      break;
    default:
      hf = hf_unknown;
      break;
    }
    tokenoffset = 2;
    if (hf == hf_unknown)
      tokenoffset = 0;
    string = (char*)tvb_get_string(wmem_packet_scope(), tvb, offset + tokenoffset,
                                             linelen - tokenoffset);
    sub_ti = proto_tree_add_string(sdp_tree, hf, tvb, offset, linelen,
                                   string);

    call_sdp_subdissector(tvb_new_subset(tvb, offset + tokenoffset,
                                         linelen - tokenoffset,
                                         linelen - tokenoffset),
                          pinfo,
                          hf, sub_ti, linelen-tokenoffset,
                          &local_transport_info, &media_info);

    offset = next_offset;
  }

  if (in_media_description) {
    /* Increase the count of media channels, but don't walk off the end of the arrays. */
    if (local_transport_info.media_count < (SDP_MAX_RTP_CHANNELS-1))
      local_transport_info.media_count++;
    if (media_info.media_count < (SDP_MAX_RTP_CHANNELS-1))
      media_info.media_count++;
  }

  /* Take all of the collected strings and convert them into something permanent
   * for the life of the capture
   */
  if (transport_info == &local_transport_info)
    convert_disposable_media(transport_info, &media_info, 0);

  for (n = 0; n < local_transport_info.media_count; n++)
  {
    /* Add (s)rtp and (s)rtcp conversation, if available (overrides t38 if conversation already set) */
    /* XXX - This is a placeholder for higher layer protocols that haven't implemented the proper
     * OFFER/ANSWER functionality using setup_sdp_transport().  Once all of the higher layers
     * use setup_sdp_transport(), this should be removed
     */
    guint32 current_rtp_port = 0;

    if ((!pinfo->fd->flags.visited) && (transport_info == &local_transport_info) &&
        (transport_info->media_port[n] != 0) &&
        (transport_info->proto_bitmask[n] & (SDP_RTP_PROTO|SDP_SRTP_PROTO)) &&
        (transport_info->proto_bitmask[n] & (SDP_IPv4|SDP_IPv6))) {
      if (transport_info->proto_bitmask[n] & SDP_SRTP_PROTO) {
          srtp_info = wmem_new0(wmem_file_scope(), struct srtp_info);
          if (transport_info->encryption_algorithm != SRTP_ENC_ALG_NOT_SET) {
            srtp_info->encryption_algorithm = transport_info->encryption_algorithm;
            srtp_info->auth_algorithm       = transport_info->auth_algorithm;
            srtp_info->mki_len              = transport_info->mki_len;
            srtp_info->auth_tag_len         = transport_info->auth_tag_len;
            }
          srtp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num,
                          (transport_info->proto_bitmask[n] & SDP_VIDEO) ? TRUE : FALSE,
                           transport_info->media[n].rtp_dyn_payload, srtp_info);
      } else {
          rtp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num,
                          (transport_info->proto_bitmask[n] & SDP_VIDEO) ? TRUE : FALSE,
                          transport_info->media[n].rtp_dyn_payload);
      }
      transport_info->media[n].set_rtp = TRUE;
      /* SPRT might use the same port... */
      current_rtp_port = transport_info->media_port[n];

      if (rtcp_handle) {
        if (transport_info->proto_bitmask[n] & SDP_SRTP_PROTO) {
          srtcp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n]+1, 0, "SDP", pinfo->fd->num, srtp_info);
        } else {
          rtcp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n]+1, 0, "SDP", pinfo->fd->num);
        }
      }
    }

    /* add SPRT conversation */
    /* XXX - more placeholder functionality */
    if ((!pinfo->fd->flags.visited) && (transport_info == &local_transport_info) &&
        (transport_info->proto_bitmask[n] & SDP_SPRT_PROTO) &&
        (transport_info->proto_bitmask[n] & (SDP_IPv4|SDP_IPv6)) &&
        (sprt_handle)) {

      if (transport_info->media_port[n] == 0 && current_rtp_port) {
        sprt_add_address(pinfo, &transport_info->src_addr[n], current_rtp_port,
                         0, "SDP", pinfo->fd->num); /* will use same port as RTP */
      } else {
        sprt_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num);
      }
    }

    /* Add t38 conversation, if available and only if no rtp */
    /* XXX - more placeholder functionality */
    if ((!pinfo->fd->flags.visited) && (transport_info == &local_transport_info) &&
        (transport_info->media_port[n] != 0) &&
        !transport_info->media[n].set_rtp &&
        (transport_info->proto_bitmask[n] & SDP_T38_PROTO) &&
        (transport_info->proto_bitmask[n] & SDP_IPv4)) {
      t38_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], 0, "SDP", pinfo->fd->num);
    }

    /* Add MSRP conversation.  Uses addresses discovered in attribute
       rather than connection information of media session line */
    /* XXX - more placeholder functionality */
    if ((!pinfo->fd->flags.visited) && (transport_info == &local_transport_info) &&
        (transport_info->proto_bitmask[n] & SDP_MSRP_PROTO) &&
        (transport_info->proto_bitmask[n] & SDP_MSRP_IPv4) &&
        msrp_handle) {
        msrp_add_address(pinfo, &transport_info->src_addr[n], transport_info->media_port[n], "SDP", pinfo->fd->num);
    }

    if (local_transport_info.media_port[n] != 0) {
      /* Create the RTP summary str for the Voip Call analysis.
       * XXX - Currently this is based only on the current packet
       */
      for (i = 0; i < local_transport_info.media[n].pt_count; i++)
      {
        /* if the payload type is dynamic (96 to 127), check the hash table to add the desc in the SDP summary */
        if ((local_transport_info.media[n].pt[i] >= 96) && (local_transport_info.media[n].pt[i] <= 127)) {
          encoding_name_and_rate_t *encoding_name_and_rate_pt =
            (encoding_name_and_rate_t *)g_hash_table_lookup(
            local_transport_info.media[n].rtp_dyn_payload,
            &local_transport_info.media[n].pt[i]);
          if (encoding_name_and_rate_pt) {
            if (strlen(sdp_pi->summary_str))
              g_strlcat(sdp_pi->summary_str, " ", 50);
            g_strlcat(sdp_pi->summary_str, encoding_name_and_rate_pt->encoding_name, 50);
          } else {
            char num_pt[10];
            g_snprintf(num_pt, 10, "%u", local_transport_info.media[n].pt[i]);
            if (strlen(sdp_pi->summary_str))
              g_strlcat(sdp_pi->summary_str, " ", 50);
            g_strlcat(sdp_pi->summary_str, num_pt, 50);
          }
        } else {
          if (strlen(sdp_pi->summary_str))
            g_strlcat(sdp_pi->summary_str, " ", 50);
          g_strlcat(sdp_pi->summary_str,
                    val_to_str_ext(local_transport_info.media[n].pt[i], &rtp_payload_type_short_vals_ext, "%u"),
                    50);
        }
      }
    }

    /* Free the hash table if we did't assigned it to a conv use it */
    /* XXX - more placeholder functionality */
    if ((transport_info == &local_transport_info) &&
        !transport_info->media[n].set_rtp)
    {
      rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
      transport_info->media[n].rtp_dyn_payload = NULL;
    }

    /* Create the T38 summary str for the Voip Call analysis
     * XXX - Currently this is based only on the current packet
     */
    if ((local_transport_info.media_port[n] != 0) &&
        (local_transport_info.proto_bitmask[n] & SDP_T38_PROTO)) {
      if (strlen(sdp_pi->summary_str))
        g_strlcat(sdp_pi->summary_str, " ", 50);
      g_strlcat(sdp_pi->summary_str, "t38", 50);
    }
  }

  /* Free the remainded hash tables not used */
  /* XXX - more placeholder functionality */
  if (transport_info == &local_transport_info) {
    for (n = transport_info->media_count; n < SDP_MAX_RTP_CHANNELS; n++)
    {
      if (!transport_info->media[n].set_rtp)
      {
        rtp_free_hash_dyn_payload(transport_info->media[n].rtp_dyn_payload);
        transport_info->media[n].rtp_dyn_payload = NULL;
      }
    }
  }

  datalen = tvb_length_remaining(tvb, offset);
  if (datalen > 0) {
    proto_tree_add_text(sdp_tree, tvb, offset, datalen, "Data (%d bytes)",  datalen);
  }
  /* Report this packet to the tap */
  tap_queue_packet(sdp_tap, pinfo, sdp_pi);
}

void
proto_register_sdp(void)
{
  static hf_register_info hf[] = {
    { &hf_protocol_version,
      { "Session Description Protocol Version (v)", "sdp.version",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner,
      { "Owner/Creator, Session Id (o)",
        "sdp.owner", FT_STRING, BASE_NONE, NULL,
        0x0, NULL, HFILL}
    },
    { &hf_session_name,
      { "Session Name (s)", "sdp.session_name",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_session_info,
      { "Session Information (i)", "sdp.session_info",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_uri,
      { "URI of Description (u)", "sdp.uri",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_email,
      { "E-mail Address (e)", "sdp.email",
        FT_STRING, BASE_NONE, NULL, 0x0,
        "E-mail Address", HFILL }
    },
    { &hf_phone,
      { "Phone Number (p)", "sdp.phone",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info,
      { "Connection Information (c)", "sdp.connection_info",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_bandwidth,
      { "Bandwidth Information (b)", "sdp.bandwidth",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_timezone,
      { "Time Zone Adjustments (z)", "sdp.timezone",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_encryption_key,
      { "Encryption Key (k)", "sdp.encryption_key",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_session_attribute,
      { "Session Attribute (a)", "sdp.session_attr",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_attribute,
      { "Media Attribute (a)", "sdp.media_attr",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_time,
      { "Time Description, active time (t)",
        "sdp.time", FT_STRING, BASE_NONE, NULL,
        0x0, NULL, HFILL }
    },
    { &hf_repeat_time,
      { "Repeat Time (r)", "sdp.repeat_time",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media,
      { "Media Description, name and address (m)",
        "sdp.media", FT_STRING, BASE_NONE, NULL,
        0x0, NULL, HFILL }
    },
    { &hf_media_title,
      { "Media Title (i)", "sdp.media_title",
        FT_STRING, BASE_NONE, NULL, 0x0,
        "Media Title", HFILL }
    },
    { &hf_unknown,
      { "Unknown", "sdp.unknown",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_invalid,
      { "Invalid line", "sdp.invalid",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_username,
      { "Owner Username", "sdp.owner.username",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_sessionid,
      { "Session ID", "sdp.owner.sessionid",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_version,
      { "Session Version", "sdp.owner.version",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_network_type,
      { "Owner Network Type", "sdp.owner.network_type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_address_type,
      { "Owner Address Type", "sdp.owner.address_type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_owner_address,
      { "Owner Address", "sdp.owner.address",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info_network_type,
      { "Connection Network Type", "sdp.connection_info.network_type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info_address_type,
      { "Connection Address Type", "sdp.connection_info.address_type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info_connection_address,
      { "Connection Address", "sdp.connection_info.address",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info_ttl,
      { "Connection TTL", "sdp.connection_info.ttl",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_connection_info_num_addr,
      { "Connection Number of Addresses", "sdp.connection_info.num_addr",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_bandwidth_modifier,
      { "Bandwidth Modifier", "sdp.bandwidth.modifier",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_bandwidth_value,
      { "Bandwidth Value", "sdp.bandwidth.value",
        FT_STRING, BASE_NONE, NULL, 0x0,
        "Bandwidth Value (in kbits/s)", HFILL }
    },
    { &hf_time_start,
      { "Session Start Time", "sdp.time.start",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_time_stop,
      { "Session Stop Time", "sdp.time.stop",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_repeat_time_interval,
      { "Repeat Interval", "sdp.repeat_time.interval",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_repeat_time_duration,
      { "Repeat Duration", "sdp.repeat_time.duration",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_repeat_time_offset,
      { "Repeat Offset", "sdp.repeat_time.offset",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_timezone_time,
      { "Timezone Time", "sdp.timezone.time",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_timezone_offset,
      { "Timezone Offset", "sdp.timezone.offset",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_encryption_key_type,
      { "Key Type", "sdp.encryption_key.type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_encryption_key_data,
      { "Key Data", "sdp.encryption_key.data",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_session_attribute_field,
      { "Session Attribute Fieldname", "sdp.session_attr.field",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_session_attribute_value,
      { "Session Attribute Value", "sdp.session_attr.value",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_media,
      { "Media Type", "sdp.media.media",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_port,
      { "Media Port", "sdp.media.port",
        FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_portcount,
      { "Media Port Count", "sdp.media.portcount",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_proto,
      { "Media Protocol", "sdp.media.proto",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_format,
      { "Media Format", "sdp.media.format",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_attribute_field,
      { "Media Attribute Fieldname", "sdp.media_attribute.field",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_attribute_value,
      { "Media Attribute Value", "sdp.media_attribute.value",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_encoding_name,
      { "MIME Type", "sdp.mime.type",
        FT_STRING, BASE_NONE, NULL, 0x0,
        "SDP MIME Type", HFILL }
    },
    { &hf_media_sample_rate,
      { "Sample Rate", "sdp.sample_rate",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_media_format_specific_parameter,
      { "Media format specific parameters", "sdp.fmtp.parameter",
        FT_STRING, BASE_NONE, NULL, 0x0,
        "Format specific parameter(fmtp)", HFILL }
    },
    { &hf_ipbcp_version,
      { "IPBCP Protocol Version", "sdp.ipbcp.version",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_ipbcp_type,
      { "IPBCP Command Type", "sdp.ipbcp.command",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    {&hf_sdp_fmtp_mpeg4_profile_level_id,
     { "Level Code", "sdp.fmtp.profile_level_id",
       FT_UINT32, BASE_DEC, VALS(mp4ves_level_indication_vals), 0x0,
       NULL, HFILL }
    },
    { &hf_sdp_fmtp_h263_profile,
      { "Profile", "sdp.fmtp.h263profile",
        FT_UINT32, BASE_DEC, VALS(h263_profile_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_fmtp_h263_level,
      { "Level", "sdp.fmtp.h263level",
        FT_UINT32, BASE_DEC, VALS(h263_level_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_h264_packetization_mode,
      { "Packetization mode", "sdp.fmtp.h264_packetization_mode",
        FT_UINT32, BASE_DEC, VALS(h264_packetization_mode_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_SDPh223LogicalChannelParameters,
      { "h223LogicalChannelParameters", "sdp.h223LogicalChannelParameters",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }
    },
    { &hf_key_mgmt_att_value,
      { "Key Management", "sdp.key_mgmt",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_key_mgmt_prtcl_id,
      { "Key Management Protocol (kmpid)", "sdp.key_mgmt.kmpid",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_key_mgmt_data,
      { "Key Management Data", "sdp.key_mgmt.data",
        FT_BYTES, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_tag,
      { "tag", "sdp.crypto.tag",
        FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_crypto_suite,
      { "Crypto suite", "sdp.crypto.crypto_suite",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_master_key,
      { "Master Key", "sdp.crypto.master_key",
        FT_BYTES, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_master_salt,
      { "Master salt", "sdp.crypto.master_salt",
        FT_BYTES, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_lifetime,
      { "Lifetime", "sdp.crypto.lifetime",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_mki,
      { "mki-value", "sdp.crypto.mki-valu",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_sdp_crypto_mki_length,
      { "mki_length", "sdp.crypto.mki_length",
        FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },
  };
  static gint *ett[] = {
    &ett_sdp,
    &ett_sdp_owner,
    &ett_sdp_connection_info,
    &ett_sdp_bandwidth,
    &ett_sdp_time,
    &ett_sdp_repeat_time,
    &ett_sdp_timezone,
    &ett_sdp_encryption_key,
    &ett_sdp_session_attribute,
    &ett_sdp_media,
    &ett_sdp_media_attribute,
    &ett_sdp_fmtp,
    &ett_sdp_key_mgmt,
    &ett_sdp_crypto_key_parameters,
  };

  static ei_register_info ei[] = {
     { &ei_sdp_invalid_key_param, { "sdp.invalid_key_param", PI_MALFORMED, PI_NOTE, "Invalid key-param (no ':' delimiter)", EXPFILL }},
     { &ei_sdp_invalid_line, { "sdp.invalid_line", PI_MALFORMED, PI_NOTE, "Invalid SDP line (no '=' delimiter)", EXPFILL }},
  };

  module_t *sdp_module;
  expert_module_t* expert_sdp;

  proto_sdp = proto_register_protocol("Session Description Protocol",
                                      "SDP", "sdp");
  proto_register_field_array(proto_sdp, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));
  expert_sdp = expert_register_protocol(proto_sdp);
  expert_register_field_array(expert_sdp, ei, array_length(ei));

  key_mgmt_dissector_table = register_dissector_table("key_mgmt",
                                                      "Key Management", FT_STRING, BASE_NONE);
  /*
   * Preferences registration
   */
  sdp_module = prefs_register_protocol(proto_sdp, NULL);
  prefs_register_bool_preference(sdp_module, "establish_conversation",
                                 "Establish Media Conversation",
                                 "Specifies that RTP/RTCP/T.38/MSRP/etc streams are decoded based "
                                 "upon port numbers found in SDP payload",
                                 &global_sdp_establish_conversation);

  sdp_transport_reqs = wmem_tree_new_autoreset(wmem_epan_scope(), wmem_file_scope());
  sdp_transport_rsps = wmem_tree_new_autoreset(wmem_epan_scope(), wmem_file_scope());

  /*
   * Register the dissector by name, so other dissectors can
   * grab it by name rather than just referring to it directly.
   */
  register_dissector("sdp", dissect_sdp, proto_sdp);

  /* Register for tapping */
  sdp_tap = register_tap("sdp");
}

void
proto_reg_handoff_sdp(void)
{
  dissector_handle_t sdp_handle;

  rtcp_handle   = find_dissector("rtcp");
  msrp_handle   = find_dissector("msrp");
  sprt_handle   = find_dissector("sprt");
  h264_handle   = find_dissector("h264");
  mp4ves_handle = find_dissector("mp4ves");

  proto_sprt    = dissector_handle_get_protocol_index(find_dissector("sprt"));

  sdp_handle = find_dissector("sdp");
  dissector_add_string("media_type", "application/sdp", sdp_handle);
  dissector_add_uint("bctp.tpi", 0x20, sdp_handle);
}
