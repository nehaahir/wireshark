/* tap-smbsids.c
 * smbstat   2003 Ronnie Sahlberg
 *
 * $Id: tap-smbsids.c 53311 2013-11-14 06:21:02Z etxrab $
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "epan/packet_info.h"
#include <epan/dissectors/packet-smb-sidsnooping.h>
#include <epan/tap.h>
#include <epan/stat_cmd_args.h>
#include "epan/value_string.h"
#include <epan/dissectors/packet-smb.h>

void register_tap_listener_smbsids(void);

static int
smbsids_packet(void *pss _U_, packet_info *pinfo _U_, epan_dissect_t *edt _U_, const void *psi _U_)
{
	return 1;
}

static void
enum_sids(gpointer key _U_, gpointer value, gpointer userdata _U_)
{
	sid_name *sn=(sid_name *)value;

	printf("%-60s %s\n", sn->sid, sn->name);
	return;
}

static void
smbsids_draw(void *pss _U_)
{
	printf("\n");
	printf("===================================================================\n");
	printf("SMB SID List:\n");
	g_hash_table_foreach(sid_name_table, enum_sids, NULL);
	printf("===================================================================\n");
}


static void
smbsids_init(const char *opt_arg _U_, void* userdata _U_)
{
	GString *error_string;

	if(!sid_name_snooping){
		fprintf(stderr,"The -z smb,sids function needs SMB/SID-Snooping to be enabled.\n");
		fprintf(stderr,"Either enable Edit/Preferences/Protocols/SMB/Snoop SID name mappings  in wireshark\n");
		fprintf(stderr,"or override the preference file by specifying\n");
		fprintf(stderr,"  -o \"smb.sid_name_snooping=TRUE\"\n");
		fprintf(stderr,"on the tshark command line.\n");
		exit(1);
	}


	error_string=register_tap_listener("smb", NULL, NULL, 0, NULL, smbsids_packet, smbsids_draw);
	if(error_string){
		fprintf(stderr, "tshark: Couldn't register smb,sids tap:%s\n",
		    error_string->str);
		g_string_free(error_string, TRUE);
		exit(1);
	}
}


void
register_tap_listener_smbsids(void)
{
	register_stat_cmd_arg("smb,sids", smbsids_init,NULL);
}

