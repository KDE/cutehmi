#!/bin/sh
#
# Copyright (c) 2014, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# Simple script to remove carriage return character (Windows style new line).
#
# usage: rmcr.sh file
# example: rmcr.sh xfile
#
# parameters:
# file - file.
#
# required tools: sh, tr, mv, stat, grep, cut, touch.


function usage()
{
    echo "usage: $0 file"
}

file=$1

if [ ! -e $file ]; then
    echo $file "does not exist"
	exit 1
fi	

if [ $# -lt 1 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

echo $file
timestamp=`stat $file | grep 'Modify: ' | cut -d ' ' -f 2,3,4`
<$file tr -d '\r' > $file.tr
mv $file.tr $file
touch -md "$timestamp" $file

