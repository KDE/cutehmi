#!/usr/bin/env bash

$EXTRACT_TR_STRINGS `find ./extensions/CuteHMI.2 -name \*.qml -o -name \*.cpp -o -name \*.hpp` -I ./extensions/CuteHMI.2/include -o $podir/cutehmi-2_qt.pot
$EXTRACT_TR_STRINGS `find ./tools/cutehmi.view.4 -name \*.qml -o -name \*.cpp -o -name \*.hpp` -I ./tools/cutehmi.view.4/include -o $podir/cutehmi-view-4_qt.pot
