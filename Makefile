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


# [license, sources, guards] Output Record Separator as used in AWK.
ifeq "$(OS)" "Windows_NT"
  ORS = "\r\n"
else
  ORS = "\n"
endif

# [license] License qualifier. This is magic string that will be used when applying license to files. 
LIC_QUALIFIER = AWKGWARD

# [license] A path to file containing license text to be appended to files, commented out with double slash.
LIC_DSLASH = awkgward/LICENSE.AWKGWARD.dslash.inc

# [license] A path to file containing license text to be appended to files, commented out with hash.
LIC_HASH = awkgward/LICENSE.AWKGWARD.hash.inc

# [license] Directories containing CMake files.
CMAKE_DIRS =

# [license] Directories containing QML files.
QML_DIRS =

# [license, sources] Directories containing source files.
SOURCE_DIRS =

# [license, guards] Directories containing header files.
INCLUDE_DIRS =

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
		@echo "Use CMake if you wish to build the software."
		@echo ""
		@echo "Make targets are:"
		@echo "help - displays this info."
		@echo "license - append license footer to source and header files."
		@echo "sources - generate list of sources and put them into CMakeLists.txt."
		@echo "guards - update include guards."
		@echo "doc - generate documentation (subtargets are doc_qdoc and doc_doxygen)."
		@echo "qmltypes - generate QML typeinfo files."
		@echo "newlines - remove carriage return characters (obsolete; use dos2unix instead)."

license: $(LIC_DSLASH) $(LIC_HASH)
		@echo "Putting license..."
		@$(FIND) $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec $(SH) awkgward/putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) $(ORS) $(FIND) \;
		@$(FIND) $(SOURCE_DIRS) \
		\( -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in' \) \
		-exec $(SH) awkgward/putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) $(ORS) $(FIND) \;
		@$(FIND) $(CMAKE_DIRS) \
		\( -name '*.cmake' -o -name 'CMakeLists.txt' \) \
		-exec $(SH) awkgward/putlic.sh {} $(LIC_HASH) hash $(LIC_QUALIFIER) $(ORS) $(FIND) \;
		@$(FIND) $(QML_DIRS) \
		\( -name '*.qml' \) \
		-exec $(SH) awkgward/putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) $(ORS) $(FIND) \;
		@$(FIND) $(CMAKE_DIRS) \
		\( -name '*.cmake' -o -name 'CMakeLists.txt' \) \
		-exec $(SH) awkgward/putlic.sh {} $(LIC_HASH) hash $(LIC_QUALIFIER) $(ORS) $(FIND) \;

sources: CMakeLists.txt
		@echo "Generating list of sources..."
		@$(AWK) -v ORS=$(ORS) -v find="$(FIND)" -v src_dirs="$(SOURCE_DIRS)" -v src_files="*.cpp;*.c" -f awkgward/cmakesrcs.awk CMakeLists.txt > CMakeLists.txt.new
		@mv CMakeLists.txt.new CMakeLists.txt

guards:
	    @echo "Updating include guards..."
		@$(FIND) $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec $(SH) awkgward/awkgward.sh $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(ORS) \;

doc: doc_qdoc doc_doxygen

doc_qdoc: $(DOC_QDOC_FILES)
		@$(foreach file, $^, $(QDOC) $(file);) 

doc_doxygen: $(DOC_DOXYGEN_FILES)
		@$(foreach file, $^, $(DOXYGEN) $(file);) 

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

