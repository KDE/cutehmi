#!/bin/sh
#
# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# For a given Doxygen file path, prints product directory relative to the
# directory containing a class of products (such as extensions or tools).
#
# usage: relproddir.sh product_file 
# example: relproddir.sh extensions/CuteHMI/Test.0/cutehmi.doxygen.Doxyfile
#
# parameters:
# product_file - file path.
#
# required tools: sh, dirname, echo.


usage()
{
    echo "usage: $0 product_file"
}

product_file=$1

if [ ! -e $product_file ]; then
	echo $product_file "does not exist"
	exit 1
fi	

if [ $# -lt 1 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

dir=$(dirname $product_file)
productdir=${dir#*/}
echo $productdir

