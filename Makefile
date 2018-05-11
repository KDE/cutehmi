# Copyright (c) 2016, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling, binging, yahooing or downloading it from pirate bay.
# NO WARRANTY.

# Shell program.
SH = sh

# PWD (Print Working Directory) command.
PWD = pwd

# [license, sources, guards] AWK program.
AWK = gawk

# [license, sources, guards] Findutils find program (note: Windows comes with "find" which is not compatible with Findutils find).
FIND = find

# [doc_qdoc] qdoc program.
QDOC = qdoc

# [doc_doxygen] Doxygen program.
DOXYGEN = doxygen

# [qmltypes] Qt's qmlplugindump program.
QMLPLUGINDUMP = qmlplugindump


# [help] Help message to be printed.

HELP_MESSAGE =

# [license, sources, guards] Output Record Separator as used in AWK.
ifeq "$(OS)" "Windows_NT"
  ORS = "\r\n"
else
  ORS = "\n"
endif

# [license] Extension of files containing license text to be appended to files, commented out with double slash.
LIC_DSLASH = LICENSE.dslash.inc

# [license] Extension of files containing license text to be appended to files, commented out with hash.
LIC_HASH = LICENSE.hash.inc

# [license] Directories containing CMake files.
CMAKE_DIRS =

# [license] CMake file types.
CMAKE_FILE_TYPES = "*.cmake CMakeLists.txt"

# [license] Directories containing QML files.
QML_DIRS =

# [license] QML file types.
QML_FILE_TYPES = "*.qml"

# [license, sources] Directories containing source files.
SOURCE_DIRS =

# [license] Source file types.
SOURCE_FILE_TYPES = "*.cpp *.c *.cpp.in"

# [license, guards] Directories containing header files.
INCLUDE_DIRS =

# [license] Include file types.
INCLUDE_FILE_TYPES = "*.hpp *.h hpp.in"

# [guards] A prefix used for include guards.
INCLUDE_GUARD_PREFIX = "AWKGWARD_"

# [doc_doxygen] List of Doxygen files.
DOC_DOXYGEN_FILES = 

# [doc_qdoc] List of qdoc files.
DOC_QDOC_FILES =

# [qmltypes] Extra library paths to be used when generating qmltypes.
QMLTYPES_EXTRAPATH =

# [qmltypes] A list of semicolon separated dump commands as passed to qmlplugindump.
QMLTYPES_DUMPS =

# Makefile.project may override variables defined above.
-include Makefile.project

# Makefile.user may override variables defined above.
-include Makefile.user

.PHONY: help license sources guards doc doc_qdoc doc_doxygen qmltypes newlines

help:
		@echo "This Makefile is responsible for code maintenance, not building."
		@echo $(HELP_MESSAGE)
		@echo ""
		@echo "Make targets are:"
		@echo "help - displays this info."
		@echo "license - append license footer to files."
		@echo "sources - generate list of sources and put them into CMakeLists.txt."
		@echo "guards - update include guards."
		@echo "doc - generate documentation (subtargets are doc_qdoc and doc_doxygen)."
		@echo "qmltypes - generate QML typeinfo files."
		@echo "newlines - remove carriage return characters (obsolete; use dos2unix instead)."

license:
		@echo "Putting license..."
		@$(foreach directory, $(INCLUDE_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(INCLUDE_FILE_TYPES) $(ORS) $(FIND); )
		@$(foreach directory, $(SOURCE_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(SOURCE_FILE_TYPES) $(ORS) $(FIND); )
		@$(foreach directory, $(CMAKE_DIRS), awkgward/makelic.sh $(LIC_HASH) hash $(directory) $(CMAKE_FILE_TYPES) $(ORS) $(FIND); )
		@$(foreach directory, $(QML_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(QML_FILE_TYPES) $(ORS) $(FIND); )

sources: CMakeLists.txt
		@echo "Generating list of sources..."
		@$(AWK) -v ORS=$(ORS) -v find="$(FIND)" -v src_dirs="$(SOURCE_DIRS)" -v src_files="*.cpp;*.c" -f awkgward/cmakesrcs.awk CMakeLists.txt > CMakeLists.txt.new
		@mv CMakeLists.txt.new CMakeLists.txt

guards:
	    @echo "Updating include guards..."
		@$(FIND) $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec $(SH) awkgward/awkgward.sh $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(ORS) \;

doc: doc_doxygen

doc_qdoc: $(DOC_QDOC_FILES)
		@$(foreach file, $^, $(QDOC) $(file);) 

doc_doxygen:
		@$(FIND) $(DOXYGEN_DIRS) \
		\( -name 'Doxyfile' -o -name '*.Doxyfile' \) \
		-execdir $(DOXYGEN) {} \;

doc_clean:
		@$(FIND) $(DOXYGEN_OUTPUT_DIRS) -type f -delete

qmltypes:
		@$(SH) awkgward/qmltypes.sh $(QMLPLUGINDUMP) $(QMLTYPES_DUMPS) $(QMLTYPES_EXTRAPATH)

newlines:
		@echo "Removing carriage return..."
		@$(FIND) $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec $(SH) awkgward/rmcr.sh {} \;
		@$(FIND) $(SOURCE_DIRS) \
		\( -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in' \) \
		-exec $(SH) awkgward/rmcr.sh {} \;

