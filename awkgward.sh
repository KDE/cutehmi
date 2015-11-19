#!/bin/sh
#
# Copyright (c) 2014, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# A chain of commands to update header file include guard.
#
# usage: awkgward.sh awk_program header_file
# example: awkgward.sh gawk header.hpp
#
# parameters:
# awk_program - name of AWK implementation.
# header_file - header file.
# prefix - include guard prefix
# ORS - output record separator (new lines style; typically: "\n" - unix mac "\r\n" - windows).
#
# required tools: sh, awk, echo, mv, awkgward.awk


function usage()
{
    echo "usage: $0 awk_program header_file [prefix] [ORS]"
}

if [ ! -e $2 ]; then
	echo $2 "does not exist"
	exit 1
fi	

if [ $# -lt 2 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

if [ $# -gt 2 ]; then
    prefix=$3;
else
    prefix=""
fi

if [ $# -gt 3 ]; then
    ors=$4;
else
    ors="\n"
fi

awk_program=$1
header_file=$2
echo $header_file
$awk_program -v ORS="$ors" -v prefix="$prefix" -f awkgward.awk $header_file > $header_file.awkgward
mv $header_file.awkgward $header_file

