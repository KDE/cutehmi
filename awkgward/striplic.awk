#!/bin/awk
#
# Copyright (c) 2019, Michal Policht. This file is dually licensed under terms of
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# Script deletes lines starting with "//(c):QUALIFIER" or "#(c):QUALIFIER" and
# empty lines above and below.
#
# usage: awk [-v comment="type"] [-v qualifier="QUALIFIER"] -f striplic.awk [file1 [file2 ... [fileN]]]
# example: awk -v comment="hash" -v qualifier="MYID" -f striplic.awk file1.cpp file1.hpp
#
# parameters:
# qualifier - copyright notice qualifier. Value is appended to search pattern.
# comment - comment type. Following values are available:
#           "dslash" - "//(c):QUALIFIER" pattern is used (default).
#           "hash" - "#(c):QUALIFIER" pattern is used.
#           "xml" - "<!--(c):QUALIFIER" pattern is used.
#
# required tools: awk.

BEGIN {
    if (comment == "hash")
        lic_comment = "^#\\(c\\)" qualifier ":"
    else if (comment == "xml")
        lic_comment = "^<!--\\(c\\)" qualifier ":"
    else
        lic_comment = "^//\\(c\\)" qualifier ":"
    nl_buf = ""; # New lines buffer.
}

# New line (CR+LF or LF).
/^\r?$/ {
    nl_buf = nl_buf $0 ORS; # Might consider using RT instead of ORS, but RT is gawk specific.
}

# Everything except new line
! /^\r?$/ {
    if (match($0, lic_comment))
        nl_buf = ""; # New lines above license comment are eaten.
    else {
        print nl_buf $0;
        nl_buf = "";
    }
}
