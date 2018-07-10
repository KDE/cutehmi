#!/bin/sh
#
# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# A chain of commands to update header file include guard.
#
# usage: awkgward.sh awk_program header_file [prefix] [IORS]
# example: awkgward.sh gawk header.hpp
#
# parameters:
# awk_program - name of AWK implementation.
# header_file - header file.
# prefix - include guard prefix
# IORS - input/output record separator (new lines style; typically: "\n" - unix mac "\r\n" - windows).
#
# required tools: sh, cut, grep, touch, stat, awk, echo, mv, awkgward.awk


usage()
{
    echo "usage: $0 awk_program header_file [prefix] [IORS]"
    echo "note: working directory from which this script is called"
    echo "      must be a directory containing awkgward directory."
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
    iors=$4;
else
    iors="\n"
fi

awk_program=$1
header_file=$2
echo $header_file
timestamp=`stat $header_file | grep 'Modify: ' | cut -d ' ' -f 2,3,4`
$awk_program -v ORS="$iors" -v RS="$iors" -v prefix="$prefix" -f awkgward/awkgward.awk $header_file > $header_file.awkgward
mv $header_file.awkgward $header_file
touch -md "$timestamp" $header_file

