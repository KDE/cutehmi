#!/bin/sh
#
# Copyright (c) 2016, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY. YOU WILL PAY ALL COSTS FOR ANY REPAIRS.
#
# This script calls qmlplugindump in order to generate QML typeinfo files.
# Names of files and modules are currently hard coded.
#
# usage: qmltypes.sh [extrapath]
# example: qmltypes.sh /path/to/lib1:/path/to/lib2
#
# parameters:
# qmlplugindump - command invoking qmlplugindump.
# dump_commands - a list of semicolon separated dump commands as passed to qmlplugindump.
#   Commands may take form "command > file" to dump output into a file.
# extrapath - path to be added to PATH environmental variable.
#
# required tools: sh, echo, tr, qmlplugindump


function usage()
{
    echo "usage: $0 [qmlplugindump] [dump_commands] [extrapath]"
}

if [ $# -lt 2 ]; then
    echo "error: too few arguments"
    usage
    exit 0
fi

if [ $# -gt 2 ]; then
    export PATH=$PATH:$3
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$3
fi

qmlplugindump_program=$1
dump_commands=$2

echo "Running qmlplugindump..."

dump_commands=$(echo $dump_commands | tr -d '\n')
org_IFS=$IFS
IFS=';'
dump_commands_arr=($dump_commands)
IFS=$org_IFS
for dump_command in "${dump_commands_arr[@]}"
do
    IFS='>' 
    dump_args_file=($dump_command)
    IFS=$org_IFS
    dump_args=$(echo ${dump_args_file[0]})
    if [ ${#dump_args_file[@]} -gt 1 ]; then
        dump_file=$(echo ${dump_args_file[1]} | tr -cd '[:print:]')
        echo "$qmlplugindump_program $dump_args > $dump_file"
        $qmlplugindump_program $dump_args > $dump_file
    else
        echo "$qmlplugindump_program $dump_args"
        $qmlplugindump_program $dump_args
    fi
done

echo ""
echo "In case qmlplugindump fails:"
echo "- Ensure that PATH environmental variable is being set correctly."
echo "- All dependent libraries are visible (extrapath parameter may be handy)."
echo "- Release versions of libraries are available (including QML plugin)."

