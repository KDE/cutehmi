#!/bin/sh
#
# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# For a given Doxygen file path, prints a product entry that can be used in
# a documentation.
#
# usage: docprodentry.sh doxygen_file
# example: docprodentry.sh modules/cutehmi_1/cutehmi.doxygen.Doxyfile
#
# parameters:
# doxygen_file - a Doxygen file.
#
# required tools: sh, dirname, echo, sed.


usage()
{
    echo "usage: $0 doxygen_file"
}

doxygen_file=$1

if [ ! -e $doxygen_file ]; then
	echo $doxygen_file "does not exist"
	exit 1
fi	

if [ $# -lt 1 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

dir=$(dirname $doxygen_file)
productdir=${dir#*/}
prodname=$(echo "$productdir" | sed 's|/|\.|g' | sed 's|\(.*\)\.|\1 |')
echo - \<a href=\"$productdir/index.html\"\>$prodname\<\/a\>

