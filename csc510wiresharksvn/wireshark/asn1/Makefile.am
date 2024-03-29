# Makefile.am
# Automake file for Wireshark
#
# $Id: Makefile.am 52721 2013-10-20 18:43:00Z pascal $
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 2006 Gerald Combs
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

include Custom.make

SUBDIRS =		\
	$(CUSTOM_SUBDIRS)	\
	acp133		\
	acse		\
	ansi_map	\
	ansi_tcap	\
	atn-cm		\
	atn-cpdlc	\
	atn-ulcs	\
	c1222		\
	camel		\
	cdt		\
	charging_ase	\
	cmip		\
	cmp		\
	credssp		\
	crmf		\
	cms		\
	dap		\
	dop		\
	disp		\
	dsp		\
	ess		\
	ftam		\
	gnm		\
	goose		\
	gsm_map		\
	gprscdr		\
	h225		\
	h235		\
	h245		\
	h248		\
	h282		\
	h283		\
	h323		\
	h450		\
	h450-ros	\
	h460		\
	h501		\
	HI2Operations	\
	hnbap		\
	idmp		\
	ilp		\
	inap		\
	isdn-sup	\
	lcsap		\
	ldap		\
	logotypecertextn \
	lpp		\
	lppa		\
	lppe		\
	lte-rrc		\
	m3ap		\
	mms		\
	mpeg-audio	\
	mpeg-pes	\
	nbap		\
	ns_cert_exts	\
	ocsp		\
	p1		\
	p22		\
	p7		\
	p772		\
	pcap		\
	pkcs1		\
	pkcs12		\
	pkinit		\
	pkixac		\
	pkix1explicit	\
	pkix1implicit	\
	pkixproxy	\
	pkixqualified	\
	pkixtsp		\
	pres		\
	q932		\
	q932-ros	\
	qsig		\
	ranap		\
	rnsap		\
	ros		\
	rrc		\
	rrlp		\
	rtse		\
	rua		\
	s1ap		\
	sabp		\
	sbc-ap		\
	smrse		\
	snmp		\
	spnego		\
	sv		\
	t124		\
	t125		\
	t38		\
	tcap		\
	tetra		\
	ulp		\
	wlancertextn	\
	x2ap		\
	x509af		\
	x509ce		\
	x509if		\
	x509sat

# kerberos is a handwritten dissector, don't replace
# x721 doesn't build
DONT_BUILD_SUBDIRS = \
	kerberos \
	x721

DIST_SUBDIRS = $(SUBDIRS) $(DONT_BUILD_SUBDIRS)

EXTRA_DIST = \
	Makefile.nmake	\
	Makefile.inc.nmake	\
	Makefile.preinc.nmake \
	Custom.make

MAINTAINERCLEANFILES = \
	Makefile.in

