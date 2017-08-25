#!/bin/sh
#
# Copyright (c) 2017, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# Find specific file types and apply licenses to them.
#
# usage: makelic.sh lic_ext comment work_dir file_types ORS find_program
# example: makelic.sh LICENSE.dslash.inc dslash src "*.cpp *.c" "\n"
#
# parameters:
# lic_ext - license files extension.
# comment - comment type. Passed as comment parameter to putlic.sh.
# work_dir - working directory.
#            Script looks for applicable license files also in all specified within a path parent directories!
# file_types - file types for which the license should be appliec.
# ORS - output record separator (new lines style; typically: "\n" - unix mac "\r\n\ - windows).
# find_program - command to execute findutils find binary.
#
# required tools: sh, find (findutils), putlic.sh.


lic_ext=$1
comment=$2
work_dir=$3
file_types=$4
ORS=$5
find_program=$6

function usage()
{
    echo "usage: $0 lic_ext comment work_dir file_types ORS find_program"
}

function putlic()
{
    lic_file=$1
    echo "Applying '${lic_file}' to directory '${work_dir}'" 

    lic_qualifier=${lic_file##*/}
    lic_qualifier=${lic_qualifier%%.*}
    for type in $file_types; do
        $find_program $work_dir -name "$type" -exec sh awkgward/putlic.sh {} $lic_file $comment $lic_qualifier $ORS $find_program \;
    done
}

if [ $# -lt 6 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

lic_search_dir=$work_dir
while [ 1 ]; do
    for lic_file in ${lic_search_dir}/*.${lic_ext}; do
        if [ -f $lic_file ]; then
            putlic $lic_file
        fi
    done
    case $lic_search_dir in
        *[/]* ) lic_search_dir=${lic_search_dir%/*} ;;
        * ) break 2 ;;
    esac
done

