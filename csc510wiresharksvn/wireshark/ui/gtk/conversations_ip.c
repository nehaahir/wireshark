/* conversations_ip.c
 * conversations_ip   2003 Ronnie Sahlberg
 *
 * $Id: conversations_ip.c 50772 2013-07-21 23:07:33Z darkjames $
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

#include <epan/packet.h>
#include <epan/stat_cmd_args.h>
#include <epan/tap.h>
#include <epan/dissectors/packet-ip.h>

#include "../stat_menu.h"

#include "ui/gtk/gui_stat_menu.h"
#include "ui/gtk/conversations_table.h"

static int
ip_conversation_packet(void *pct, packet_info *pinfo, epan_dissect_t *edt _U_, const void *vip)
{
	const ws_ip *iph=(ws_ip *)vip;

	add_conversation_table_data((conversations_table *)pct, &iph->ip_src, &iph->ip_dst, 0, 0, 1, pinfo->fd->pkt_len, &pinfo->rel_ts, SAT_NONE, PT_NONE);

	return 1;
}

static void
ip_conversation_init(const char *opt_arg, void* userdata _U_)
{
	const char *filter=NULL;

	if(!strncmp(opt_arg,"conv,ip,",8)){
		filter=opt_arg+8;
	} else {
		filter=NULL;
	}

	init_conversation_table(TRUE, "IPv4", "ip", filter, ip_conversation_packet);

}

void
ip_endpoints_cb(GtkAction *action _U_, gpointer user_data _U_)
{
	ip_conversation_init("conv,ip",NULL);
}

void
register_tap_listener_ip_conversation(void)
{
	register_stat_cmd_arg("conv,ip", ip_conversation_init,NULL);
	register_conversation_table(TRUE, "IPv4", "ip", NULL /*filter*/, ip_conversation_packet);
}
