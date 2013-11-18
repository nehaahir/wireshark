/* packet_comment_dialog.h
 *
 * $Id: packet_comment_dialog.h 46709 2012-12-23 04:37:58Z gerald $
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

#ifndef PACKET_COMMENT_DIALOG_H
#define PACKET_COMMENT_DIALOG_H

#include <QDialog>

namespace Ui {
class PacketCommentDialog;
}

class PacketCommentDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PacketCommentDialog(QWidget *parent = 0, QString comment = QString());
    ~PacketCommentDialog();
    QString text();
    
private slots:
    void on_buttonBox_helpRequested();

private:
    Ui::PacketCommentDialog *pc_ui_;
};

#endif // PACKET_COMMENT_DIALOG_H