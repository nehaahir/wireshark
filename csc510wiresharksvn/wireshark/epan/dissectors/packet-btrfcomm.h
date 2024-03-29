/* packet-btrfcomm.h
 *
 * $Id: packet-btrfcomm.h 53089 2013-11-05 17:48:48Z eapache $
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

#ifndef __PACKET_BTRFCOMM_H__
#define __PACKET_BTRFCOMM_H__

extern int proto_btrfcomm;

typedef struct _btrfcomm_data_t {
    guint32 interface_id;
    guint32 adapter_id;
    guint16 chandle;  /* only low 12 bits used */
    guint16 cid;
    guint8  dlci;
    guint32 remote_bd_addr_oui;
    guint32 remote_bd_addr_id;
} btrfcomm_data_t;

#endif

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
