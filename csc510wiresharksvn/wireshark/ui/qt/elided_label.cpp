/* elided_label.cpp
 *
 * $Id: elided_label.cpp 50896 2013-07-25 23:49:47Z gerald $
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

#include "elided_label.h"

#include <QFontMetrics>

ElidedLabel::ElidedLabel(QWidget *parent) :
    QLabel(parent)
{
}

void ElidedLabel::setUrl(const QString &url)
{
    url_ = url;
    updateText();
}

void ElidedLabel::resizeEvent(QResizeEvent *evt)
{
    Q_UNUSED(evt)
    updateText();
}

void ElidedLabel::updateText()
{
    QString elided_text = fontMetrics().elidedText(full_text_, Qt::ElideMiddle, width());
    if (url_.length() > 0) {
        QLabel::setText(QString("<i><a href=\"%1\">%2</a></i>")
                .arg(url_)
                .arg(elided_text)
                );
    } else {
        QLabel::setText(QString("<i>%1</i>")
                .arg(elided_text)
                );
    }
}

void ElidedLabel::clear()
{
    full_text_.clear();
    url_.clear();
    setToolTip("");
    updateText();
}

void ElidedLabel::setText(const QString &text)
{
    full_text_ = text;
    updateText();
}
