#!/bin/bash

# A small script to export some variables and run tshark or wireshark in
# valgrind on a given capture file.
#
# Copyright 2012 Jeff Morriss <jeff.morriss.ws [AT] gmail.com>
#
# $Id: valgrind-wireshark.sh 53250 2013-11-11 18:44:50Z wmeier $
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

# Directory containing tshark or wireshark.  Default current directory.
BIN_DIR=.

# Use tshark by default
COMMAND=tshark
COMMAND_ARGS="-nr"
COMMAND_ARGS2=
VALID=0
PCAP=""
TOOL="memcheck"

while getopts ":2b:C:lmnpP:rtTYwcevW" OPTCHAR ; do
    case $OPTCHAR in
        2) COMMAND_ARGS="-2 $COMMAND_ARGS" ;;
        b) BIN_DIR=$OPTARG ;;
        C) COMMAND_ARGS="-C $OPTARG $COMMAND_ARGS" ;;
        l) LEAK_CHECK="--leak-check=full" ;;
        m) TOOL="massif" ;;
        n) COMMAND_ARGS="-v"
           VALID=1 ;;
        p) TOOL="callgrind" ;;
        P) TOOL="callgrind"
           CALLGRIND_OUT_FILE="--callgrind-out-file=$OPTARG" ;;
        r) REACHABLE="--show-reachable=yes" ;;
        t) TRACK_ORIGINS="--track-origins=yes" ;;
        T) COMMAND_ARGS="-Vx $COMMAND_ARGS" ;; # "build the Tree"
        Y) COMMAND_ARGS="-Yframe $COMMAND_ARGS" ;; # Run with a read filter (but no tree)
        w) COMMAND=wireshark
           COMMAND_ARGS="-nr" ;;
        c) COMMAND=capinfos
           COMMAND_ARGS="" ;;
        e) COMMAND=editcap
           COMMAND_ARGS="-E 0.02"
           # We don't care about the output of editcap
           COMMAND_ARGS2="/dev/null" ;;
        v) VERBOSE="--num-callers=256" ;;
        W) COMMAND=wireshark
           COMMAND_ARGS=""
           VALID=1 ;;
        *) printf "Unknown option -$OPTARG!\n"
           exit ;;
    esac
done
shift $(($OPTIND - 1))

if [ $# -ge 1 ]
then
    PCAP=$1
    VALID=1
fi

if [ $VALID -eq 0 ]
then
    printf "Usage: $0 [-2] [-b bin_dir] [-c] [-e] [-C config_profile] [-l] [-m] [-n] [-p] [-r] [-t] [-T] [-w] [-v] /path/to/file.pcap\n"
    exit 1
fi

if [ "$BIN_DIR" = "." ]; then
    export WIRESHARK_RUN_FROM_BUILD_DIRECTORY=
fi

if [ "$TOOL" != "callgrind" ]; then
    export WIRESHARK_DEBUG_EP_NO_CHUNKS=
    export WIRESHARK_DEBUG_SE_NO_CHUNKS=
    export WIRESHARK_DEBUG_WMEM_OVERRIDE=simple
    export G_SLICE=always-malloc # or debug-blocks
fi

COMMAND="$BIN_DIR/$COMMAND"

if file $COMMAND | grep -q "ASCII text"; then
    if [ -x "`dirname $0`/../libtool" ]; then
        LIBTOOL="`dirname $0`/../libtool"
    else
        LIBTOOL="libtool"
    fi
    LIBTOOL="$LIBTOOL --mode=execute"
else
    LIBTOOL=""
fi

$LIBTOOL valgrind --suppressions=`dirname $0`/vg-suppressions --tool=$TOOL $CALLGRIND_OUT_FILE $VERBOSE $LEAK_CHECK $REACHABLE $TRACK_ORIGINS $COMMAND $COMMAND_ARGS $PCAP $COMMAND_ARGS2 > /dev/null
