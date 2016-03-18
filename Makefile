# Copyright (c) 2015, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling, binging, yahooing or downloading it from pirate bay.
# NO WARRANTY.
#
# Unsupported features has been commmented out.

AWK = gawk
SH = sh
LIC_QUALIFIER = MP
LIC_DSLASH = LICENSE.MP.dslash.inc
LIC_HASH = LICENSE.MP.hash.inc
INCLUDE_GUARD_PREFIX = "CUTEHMI_"
SOURCE_DIRS = AppFull/src \
			  AppLite/src \
			  LibBase/src \
			  LibWidgets/src \
			  LibModbus/src \
			  PluginModbus/src \
			  PluginModbusUI/src \
			  QML/CuteHMI/Modbus/src
INCLUDE_DIRS = AppFull/src \
			   AppLite/src \
			   LibBase/src \
			   LibWidgets/src \
			   LibModbus/src \
			   PluginModbus/src \
			   PluginModbusUI/src \
			   QML/CuteHMI/Modbus/src
CMAKE_DIRS =
ORS = "\r\n"
PWD = pwd
QMLTYPES_EXTRAPATH = $$(PWD)/../binary-CuteHMI:$$(PWD)/../libmodbus-3.1.2/src/.libs

.PHONY: help qmltypes sources license guards newlines

help:
		@echo "This Makefile is responsible for code maintenance, \
not building."
		@echo "Use qmake if you wish to build the software."
		@echo ""
		@echo "Make targets are:"
		@echo "qmltypes - generate QML typeinfo files."
		@echo "help - displays this info."
#		@echo "sources - generate list of sources and put them into CMakeLists.txt."
#		@echo "license - append license footer to source and header files."
		@echo "guards - update include guards."
#		@echo "newlines - remove carriage return characters."

qmltypes:
		@$(SH) qmltypes.sh $(QMLTYPES_EXTRAPATH)

#sources:
#		@echo "Generating list of sources..."
#		$(AWK) -v src_dirs="$(SOURCE_DIRS)" -v src_files="*.cpp;*.c" -f cmakesrcs.awk CMakeLists.txt > CMakeLists.txt.new
#		mv CMakeLists.txt.new CMakeLists.txt

license:
		@echo "Putting license..."
		@find $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) $(ORS) \;
		@find $(SOURCE_DIRS) \
		\( -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in' \) \
		-exec putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) $(ORS) \;
		@find $(CMAKE_DIRS) \
		\( -name '*.cmake' -o -name 'CMakeLists.txt' \) \
		-exec putlic.sh {} $(LIC_HASH) hash $(LIC_QUALIFIER) $(ORS) \;

guards:
	    @echo "Updating include guards..."
		@find $(INCLUDE_DIRS) -name "*.hpp" -exec $(SH) awkgward.sh $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(ORS) \;

#newlines:
#		@echo "Removing carriage return..."
#		@find $(INCLUDE_DIRS) \
#		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
#		-exec rmcr.sh {} \;
#		@find $(SOURCE_DIRS) \
#		\( -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in' \) \
#		-exec rmcr.sh {} \;

