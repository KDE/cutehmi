#!/bin/sh
#
# Copyright (c) 2010, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# A chain of commands to strip and put license into file. If license file contains
# magic phrase %YEAR% it will be replaced by a year of target file modification date.
#
# usage: putlic.sh target_file license_file [comment] [qualifier]
# example: putlic.sh script.cmake LICENSE "hash" "MYID"
#
# parameters:
# target_file - where to put license.
# license_file - file containing license.
# comment - comment type. Passed as "comment" variable to striplic.awk. 
#           Check striplic.awk for possible values.
# qualifier - copyright notice qualifier. See stiplic.awk for details.
# ORS - output record separator (new lines style; typically: "\n" - unix mac "\r\n" - windows).
#
# required tools: sh, awk, sed, echo, find (findutils), cat, rm, striplic.awk.


function usage()
{
    echo "usage: $0 target_file license_file [comment] [qualifier] [ORS]"
}

target_file=$1
license_file=$2

if [ ! -e $target_file ]; then
	echo $target_file "does not exist"
	exit 1
fi	

if [ ! -e $license_file ]; then
	echo $license_file "does not exist"
	exit 1
fi	

if [ $# -lt 2 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

if [ $# -gt 2 ]; then
    comment=$3;
else
    comment="dslash"
fi

if [ $# -gt 3 ]; then
    qualifier=$4;
else
    qualifier=""
fi

if [ $# -gt 4 ]; then
    ors=$5;
else
    ors="\n"
fi

echo $target_file
awk -v ORS="$ors" -v comment="$comment" -v qualifier="$qualifier" -f striplic.awk $target_file > $target_file.strip
year=`find $target_file -maxdepth 0 -printf "%TY"`
# Invoking sed with -b option to prevent new lines conversion
sed -b "s/%YEAR%/$year/" $license_file > $license_file.putlic
cat $target_file.strip $license_file.putlic > $target_file
rm $target_file.strip
rm $license_file.putlic
