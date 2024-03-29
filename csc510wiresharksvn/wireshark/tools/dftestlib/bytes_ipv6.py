# Copyright (c) 2013 by Gilbert Ramirez <gram@alumni.rice.edu>
#
# $Id: bytes_ipv6.py 52882 2013-10-27 00:51:54Z morriss $
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

from dftestlib import dftest

class testBytesIPv6(dftest.DFTest):
    trace_file = "ipv6.pcap"

    def test_ipv6_1(self):
        dfilter = "ipv6.dst == ff05::9999"
        self.assertDFilterCount(dfilter, 1)

    def test_ipv6_2(self):
        dfilter = "ipv6.dst == ff05::9990"
        self.assertDFilterCount(dfilter, 0)
