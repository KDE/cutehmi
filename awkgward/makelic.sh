#!/bin/sh
#
# Copyright (c) 2019, Michal Policht. This file is dually licensed under terms of
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# Find specific file types and apply license to them. Qualifier is extracted
# from license file name (being highest file extension).
#
# usage: makelic.sh lic_path comment file_types IORS find_program git_program
# example: makelic.sh LICENSE.C.dslash.inc dslash src "*.cpp *.c" "\n" find git
#
# parameters:
# lic_path - path to license file.
# comment - comment type. Passed as comment parameter to putlic.sh.
# file_types - file types for which the license should be applied.
# IORS - input/output record separator (new lines style; typically: "\n" - unix mac "\r\n\ - windows).
# find_program - command to execute findutils find.
# git - command to execute git.
#
# required tools: sh, dirname, find (findutils), putlic.sh.


lic_path=$1
comment=$2
file_types=$3
IORS=$4
find_program=$5
git_program=$6

usage()
{
    echo "usage: $0 lic_path comment file_types IORS find_program git_program"
}

if [ $# -lt 6 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi


dir=$(dirname $lic_path)
lic_filename=${lic_path##*/}
lic_ext=${lic_filename#*.}
lic_qualifier=${lic_ext%%.*}

echo "Applying '${lic_path}' to directory '${dir}'"
set -f # Turn off globbing to prevent $file_types expansion to matched files.
$find_program $dir -type f \( $file_types \) -exec sh awkgward/putlic.sh {} $lic_path $comment $lic_qualifier $IORS $find_program $git_program \;
set +f

