# CMakeLists.txt
#
# $Id: CMakeLists.txt 52884 2013-10-27 01:11:15Z morriss $
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 1998 Gerald Combs
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

set( PROTOCOL_NAME h460 )

set( PROTO_OPT _EMPTY_ )

set( EXT_ASN_FILE_LIST
)

set( ASN_FILE_LIST
	NUMBER-PORTABILITY.asn
	CIRCUIT-STATUS-MAP.asn
	CALL-PRIORITY.asn
	QOS-MONITORING-REPORT.asn
	QOS-MONITORING-EXTENDED-VOIP-REPORT.asn
	CALL-PARTY-CATEGORY.asn
	MLPP.asn
	SIGNALLING-CHANNEL-SUSPEND-REDIRECT.asn
	SIGNALLING-TRAVERSAL.asn
	MEDIA-TRAVERSAL.asn
	MESSAGE-BROADCAST.asn
)

set( EXTRA_DIST
	${ASN_FILE_LIST}
	packet-${PROTOCOL_NAME}-template.c
	${PROTOCOL_NAME}.cnf
)

set( SRC_FILES
	${EXTRA_DIST}
	${EXT_ASN_FILE_LIST}
)

set( A2W_FLAGS  )

set( EXTRA_CNF
	h225-exp.cnf
	h235-exp.cnf
	h245-exp.cnf
)

ASN2WRS()

