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
# extrapath - path to be added to PATH environmental variable.
#
# required tools: sh, echo, qmlplugindump


function usage()
{
    echo "usage: $0 [extrapath]"
}

#if [ $# -lt 1 ]; then
#    echo "error: too few arguments"
#    usage
#    exit 0
#fi

if [ $# -gt 0 ]; then
    export PATH=$PATH:$1;
fi

importpath=QML

echo "Running qmlplugindump..."

qmlplugindump CuteHMI.Modbus 1.0 $importpath > QML/CuteHMI/Modbus/QML_Modbus.qmltypes

echo ""
echo "In case qmlplugindump fails:"
echo "- Ensure that PATH environmental variable is being set correctly."
echo "- All dependent libraries are visible (extrapath parameter may be handy)."
echo "- Release versions of libraries are available (including QML plugin)."
