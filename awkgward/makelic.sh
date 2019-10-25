#!/bin/sh
#
# Copyright (c) 2019, Michal Policht. This file is dually licensed under terms of
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# Find specific file types and apply license to them.
#
# usage: makelic.sh lic_fle comment file_types IORS find_program git_program
# example: makelic.sh LICENSE.dslash.inc dslash src "*.cpp *.c" "\n" find git
#
# parameters:
# lic_file - license file.
# comment - comment type. Passed as comment parameter to putlic.sh.
# file_types - file types for which the license should be applied.
# IORS - input/output record separator (new lines style; typically: "\n" - unix mac "\r\n\ - windows).
# find_program - command to execute findutils find.
# git - command to execute git.
#
# required tools: sh, dirname, find (findutils), putlic.sh.


lic_file=$1
comment=$2
file_types=$3
IORS=$4
find_program=$5
git_program=$6

usage()
{
    echo "usage: $0 lic_file comment file_types IORS find_program git_program"
}

if [ $# -lt 6 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi


lic_file=$1
dir=$(dirname $lic_file)
lic_qualifier=${lic_file##*/}
lic_qualifier=${lic_qualifier%%.*}

echo "Applying '${lic_file}' to directory '${dir}'"
set -f # Turn off globbing to prevent $file_types expansion to matched files.
$find_program $dir -type f \( $file_types \) -exec sh awkgward/putlic.sh {} $lic_file $comment $lic_qualifier $IORS $find_program $git_program \;
set +f

