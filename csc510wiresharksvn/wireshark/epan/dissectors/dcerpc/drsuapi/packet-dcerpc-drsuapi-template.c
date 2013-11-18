/* DO NOT EDIT
 * This dissector is autogenerated
 */

/* packet-dcerpc-drsuapi.c
 * Routines for DRSUAPI packet disassembly
 *   ronnie sahlberg 2005
 *
 * $Id: packet-dcerpc-drsuapi-template.c 53099 2013-11-06 13:01:23Z mmann $
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

#include "config.h"

#include <glib.h>
#include <string.h>

#include <epan/packet.h>
#include "packet-dcerpc.h"
#include "packet-dcerpc-nt.h"
#include "packet-windows-common.h"
#include "packet-dcerpc-drsuapi.h"

static int proto_drsuapi = -1;
static int hf_drsuapi_DsReplicaSyncRequest1Info_nc_dn = -1;
ETH_HF

ETH_ETT

static int
ucarray_drsuapi_dissect_DsReplicaSyncRequest1Info_nc_dn(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	static guint32 len;
	int old_offset;

	if(di->conformant_run){
		/*just a run to handle conformant arrays, nothing to dissect 
		  but we need to remember how long this array was.
		  see packet-dcerpc.c for examples of conformant_run
		  and what it is.
		*/
		old_offset=offset;
		offset=dissect_dcerpc_uint32(tvb, offset, pinfo, NULL, drep, -1, &len);
		di->array_max_count_offset=offset-4;
		di->conformant_run=1;
		di->conformant_eaten=offset-old_offset;
		return offset;
	}

	ALIGN_TO_2_BYTES;

        if (tree && len) {
            proto_tree_add_item(tree, hf_drsuapi_DsReplicaSyncRequest1Info_nc_dn, tvb, offset,
                                len*2, ENC_UTF_16|ENC_LITTLE_ENDIAN);
        }

	offset+=2*len;
	return offset;
}

static int
drsuapi_dissect_a_string(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, int hf_index, guint32 param _U_)
{
    offset=dissect_ndr_vstring(tvb, offset, pinfo, tree, di, drep, 1, hf_index, FALSE, NULL);
    return offset;
}

ETH_CODE

void
proto_register_drsuapi(void)
{
        static hf_register_info hf[] = {
        { &hf_drsuapi_DsReplicaSyncRequest1Info_nc_dn,
          { "nc_dn", "drsuapi.DsReplicaSyncRequest1Info.nc_dn", FT_STRING, BASE_NONE,
          NULL, 0,
         NULL, HFILL }},

ETH_HFARR
	};

        static gint *ett[] = {
ETH_ETTARR
        };

        proto_drsuapi = proto_register_protocol(
                "DRSUAPI", 
		"DRSUAPI", "drsuapi");
	proto_register_field_array(proto_drsuapi, hf, array_length(hf));
        proto_register_subtree_array(ett, array_length(ett));
}

static dcerpc_sub_dissector function_dissectors[] = {
ETH_FT
	{ 0, NULL, NULL, NULL },
};

void
proto_reg_handoff_drsuapi(void)
{
ETH_HANDOFF
}

