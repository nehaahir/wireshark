/* conversations_fddi.c
 * conversations_fddi   2003 Ronnie Sahlberg
 *
 * $Id: conversations_fddi.c 50772 2013-07-21 23:07:33Z darkjames $
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

#include <string.h>

#include <gtk/gtk.h>

#include "epan/packet.h"
#include <epan/stat_cmd_args.h>
#include <epan/tap.h>
#include <epan/dissectors/packet-fddi.h>

#include "../stat_menu.h"

#include "ui/gtk/gui_stat_menu.h"
#include "ui/gtk/conversations_table.h"

static int
fddi_conversation_packet(void *pct, packet_info *pinfo, epan_dissect_t *edt _U_, const void *vip)
{
	const fddi_hdr *ehdr=(fddi_hdr *)vip;

	add_conversation_table_data((conversations_table *)pct, &ehdr->src, &ehdr->dst, 0, 0, 1, pinfo->fd->pkt_len, &pinfo->rel_ts, SAT_FDDI, PT_NONE);

	return 1;
}



static void
fddi_conversation_init(const char *opt_arg, void* userdata _U_ )
{
	const char *filter=NULL;

	if(!strncmp(opt_arg,"conv,fddi,",10)){
		filter=opt_arg+10;
	} else {
		filter=NULL;
	}

	init_conversation_table(TRUE, "FDDI", "fddi", filter, fddi_conversation_packet);

}

void
fddi_endpoints_cb(GtkAction *action _U_, gpointer user_data _U_)
{
	fddi_conversation_init("conv,fddi",NULL);
}

void
register_tap_listener_fddi_conversation(void)
{
	register_stat_cmd_arg("conv,fddi", fddi_conversation_init,NULL);
	register_conversation_table(TRUE, "FDDI", "fddi", NULL /*filter*/, fddi_conversation_packet);
}
