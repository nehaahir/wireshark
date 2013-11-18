#!/usr/bin/perl
#
# make-reg.pl
# Registration Macros Generator
#
# (c) 2006, Luis E. Garcia Onatnon <luis.ontanon@gmail.com>
#
# $Id: make-reg.pl 51965 2013-09-12 11:34:13Z stig $
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

use strict;

my @classes = ();
my @functions = ();

while (<>) {
	push @classes, $1 if /WSLUA_CLASS_DEFINE\050\s*([A-Za-z0-9]+)/;
	push @functions, $1 if  /WSLUA_FUNCTION\s+wslua_([a-z_0-9]+)/;
}

open C, ">register_wslua.c";
open H, ">declare_wslua.h";

print H "/* This file is automatically genrated by make-reg.pl do not edit */\n\n";
print C "/* This file is automatically genrated by make-reg.pl do not edit */\n\n";

print H "#define WSLUA_DECLARE_CLASSES() \\\n"; 
for (@classes) {
	print H "\tWSLUA_CLASS_DECLARE($_);\\\n"
}
print H "\n\n";

print H "#define WSLUA_DECLARE_FUNCTIONS() \\\n"; 
for (@functions) {
	print H "\tWSLUA_FUNCTION wslua_$_(lua_State* L);\\\n"
}
print H "\n\n";
print H "extern void wslua_register_classes(lua_State* L);\n"; 
print H "extern void wslua_register_functions(lua_State* L);\n"; 
print H "\n\n";

print C '#include "config.h"' . "\n";

print C '#include "wslua.h"' . "\n\n"; 
print C "static void wslua_reg_module(lua_State* L, const char *name, lua_CFunction func) { \n"; 
print C "\tlua_pushcfunction(L, func);\n";
print C "\tlua_pushstring(L, name);\n";
print C "\tlua_call(L, 1, 0);\n";
print C "}\n\n";
print C "void wslua_register_classes(lua_State* L) { \n"; 
for (@classes) {
	print C "\twslua_reg_module(L, \"${_}\", ${_}_register);\n";
}
print C "\twslua_reg_module(L, \"bit\", luaopen_bit);\n";
print C "}\n\n";


print C "void wslua_register_functions(lua_State* L) {\n"; 
for (@functions) {
	print C "\tWSLUA_REGISTER_FUNCTION($_); \n"
}
print C "}\n\n";

close H;
close C;
