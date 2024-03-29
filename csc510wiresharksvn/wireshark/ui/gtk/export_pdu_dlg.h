/* export_pdu_dlg.h
 * Routines for exporting PDU:s to file
 *
 * $Id: export_pdu_dlg.h 51459 2013-08-21 21:44:48Z martink $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
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

#ifndef __EXPORT_PDU_DLG_H__
#define __EXPORT_PDU_DLG_H__

void export_pdu_show_cb(GtkWidget *widget, gpointer data);
void do_export_pdu(gpointer data);

#endif /* __EXPORT_PDU_DLG_H__ */
