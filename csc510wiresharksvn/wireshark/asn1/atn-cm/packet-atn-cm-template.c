/* c-basic-offset: 2; tab-width: 2; indent-tabs-mode: t
 * vi: set shiftwidth=2 tabstop=2 noexpandtab:
 * :indentSize=2:tabSize=2:noTabs=false:
 */


/* packet-atn-cm.c
 * By Mathias Guettler <guettler@web.de>
 * Copyright 2013
 *
 * $Id: packet-atn-cm-template.c 53230 2013-11-10 15:59:37Z darkjames $
 *
 * Routines for ATN context management protocol packet disassembly.
 * ATN context management allows an aircraft
 * to log on to a ground facility.

 * details see:
 * http://en.wikipedia.org/wiki/CPDLC
 * http://members.optusnet.com.au/~cjr/introduction.htm

 * standards:
 * http://legacy.icao.int/anb/panels/acp/repository.cfm

 * note:
 * We are dealing with ATN/CPDLC aka ICAO Doc 9705 Ed2 here
 * (CPDLC may also be transmitted via ACARS/AOA aka "FANS-1/A ").


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
#include <epan/packet.h>
#include <epan/exceptions.h>
#include <epan/conversation.h>
#include <epan/dissectors/packet-ber.h>
#include <epan/dissectors/packet-per.h>
#include <epan/conversation.h>

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "packet-atn-ulcs.h"

#define ATN_CM_PROTO "ICAO Doc9705 CM"

#include "packet-atn-cm-hf.c"

#include "packet-atn-cm-ett.c"
static gint ett_atn_cm = -1;

#include "packet-atn-cm-fn.c"
static int proto_atn_cm = -1;

static int
dissect_atn_cm(
		tvbuff_t *tvb,
		packet_info *pinfo,
		proto_tree *tree,
		void *data _U_)
{
		int 	type = no_msg;
		proto_item *ti = NULL;
		proto_tree *sub_tree = NULL;
	
		ti = proto_tree_add_text(
			tree,
			tvb,
			0,
			tvb_reported_length_remaining(tvb, 0) ,
			ATN_CM_PROTO);

		sub_tree = proto_item_add_subtree(
			ti,
			ett_atn_cm);
		
		/* ti = proto_tree_add_item(tree, proto_atn_cm, tvb, 0, 0 , FALSE); */
		/* sub_tree = proto_item_add_subtree(ti, ett_atn_cm_pdu); */
		
		/* determine whether it is uplink or downlink */
		type = check_heur_msg_type(pinfo);

		switch(type){
				case um:
						dissect_CMGroundMessage_PDU(
							tvb,
							pinfo,
							sub_tree);
						break;
				case dm:
						dissect_CMAircraftMessage_PDU(
							tvb,
							pinfo,
							sub_tree);
						break;
				default:
						break;
		}
		return tvb_reported_length_remaining(tvb, 0);
}

static gboolean
dissect_atn_cm_heur(
		tvbuff_t *tvb,
		packet_info *pinfo,
		proto_tree *tree,
		void *data _U_)
{
		atn_conversation_t *atn_cv = NULL;
		gboolean is_atn_cm = FALSE;
		int type;

		/* determine whether it is uplink or downlink */
		type = check_heur_msg_type(pinfo);

		/* heuristically decode message */
		switch(type){
				case um:
						TRY { 
								dissect_CMGroundMessage_PDU(
									tvb,
									pinfo,
									NULL);
								/* no exception thrown: looks like it is a CM PDU */
								is_atn_cm = TRUE; }
						CATCH_ALL {
								is_atn_cm = FALSE; }
						ENDTRY;
						break;
				case dm:
						TRY {
								dissect_CMAircraftMessage_PDU(
										tvb,
										pinfo,
										NULL);
								/* no exception thrown: looks like it is a CM PDU */
								is_atn_cm = TRUE;}
						CATCH_ALL {
								is_atn_cm = FALSE; }
						ENDTRY;
						break;
				default:
						break;
		}
		
		if (is_atn_cm  == TRUE) {
				/* note: */
				/* all subsequent PDU's belonging to this conversation are considered CM */
				/* if the first CM PDU has been decoded succesfully */
				/* (This is done in "atn-ulcs" by using "call_dissector_with_data()") */
		
				/* DT: dstref present, srcref is always zero */
				if((pinfo->clnp_dstref) &&
						(!pinfo->clnp_srcref)){

					atn_cv = find_atn_conversation(
								&pinfo->dst,
								pinfo->clnp_dstref,
								&pinfo->src );
				}
				/* CR: srcref present, dstref is always zero */
				if((!pinfo->clnp_dstref) &&
						(pinfo->clnp_srcref)){

					atn_cv = find_atn_conversation(
								&pinfo->src,
								pinfo->clnp_srcref,
								&pinfo->dst );

				}
				/* CC: srcref and dstref present  */
				if((pinfo->clnp_dstref) &&
						(pinfo->clnp_srcref)){
						atn_cv = find_atn_conversation(
								&pinfo->src,
								pinfo->clnp_srcref,
								&pinfo->dst );
				}
				if(atn_cv){
						atn_cv->ae_qualifier = cma;
				}
				dissect_atn_cm(
						tvb,
						pinfo,
						tree,
						NULL);
		}

		return is_atn_cm;
}


void proto_register_atn_cm (void)
{
    static hf_register_info hf_atn_cm[] = {
					#include "packet-atn-cm-hfarr.c"
    };
		static gint *ett[] = {
			#include "packet-atn-cm-ettarr.c"
			&ett_atn_cm
		};
		
		/* register CM application */
		proto_atn_cm = proto_register_protocol(
				ATN_CM_PROTO ,
				"ATN-CM",
				"atn-cm");

		proto_register_field_array(
				proto_atn_cm,
				hf_atn_cm,
				array_length(hf_atn_cm));

		proto_register_subtree_array(
				ett,
				array_length(ett));

		new_register_dissector(
				"atn-cm",
				dissect_atn_cm,
				proto_atn_cm);
}

void proto_reg_handoff_atn_cm(void)
{
		/* add session dissector to subdissector list*/
		heur_dissector_add(
				"atn-ulcs",
				dissect_atn_cm_heur,
				proto_atn_cm);
}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 2
 * tab-width: 2
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=2 tabstop=2 noexpandtab:
 * :indentSize=2:tabSize=2:noTabs=false:
 */

