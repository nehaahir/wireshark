/*
 * packet-diameter.h
 *
 * Definitions for Diameter packet disassembly
 * $Id: packet-diameter.h 50796 2013-07-22 20:44:01Z etxrab $
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

/* Request-Answer Pair */
typedef struct _diameter_req_ans_pair_t
{
	guint32		hop_by_hop_id;
	guint32		end_to_end_id;
	guint32		cmd_code;
	guint32		result_code;
	const char*	cmd_str;
	guint32 	req_frame; 	/* frame number in which request was seen */
	guint32		ans_frame;	/* frame number in which answer was seen */
	nstime_t	req_time;
	nstime_t	srt_time;
	gboolean	processing_request; /* TRUE if processing request, FALSE if processing answer. */
} diameter_req_ans_pair_t;

/* Info needed by AVP sub dissectors */
typedef struct _diam_sub_dis_t {
	guint32 application_id;
	guint32 feature_list_id;
} diam_sub_dis_t;
