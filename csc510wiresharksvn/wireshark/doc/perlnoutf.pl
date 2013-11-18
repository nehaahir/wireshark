#!/usr/bin/perl -w

# $Id: perlnoutf.pl 52941 2013-10-29 04:05:27Z gerald $

# Call another Perl script, passing our caller's arguments, with
# environment variables unset so perl doesn't interpret bytes as UTF-8
# characters.

use strict;

delete $ENV{LANG};
delete $ENV{LANGUAGE};
delete $ENV{LC_ALL};
delete $ENV{LC_CTYPE};

system("$^X -w @ARGV");
