# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling, binging, yahooing or downloading it from pirate bay.
# NO WARRANTY.


first: help

# [help] Help message to be printed.

HELP_MESSAGE =

# [license] Names of files containing license text to be appended to files, commented out with double slash.
LIC_DSLASH = LICENSE.dslash.inc

# [license] Names of files containing license text to be appended to files, commented out with hash.
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

include Makefile.project

.PHONY: help description path license guards doc doc_clean doc_doxygen ports

help: description path
		@echo --------------------------------------------------------------------------------
		@echo Make targets are:
		@echo help - displays this info.
		@echo license - append license footer to files.
		@echo guards - update include guards.
		@echo doc[_clean] - generate [or clean] documentation.
		@echo ports[_clean][_jobs] - make [clean][build jobs of] external libraries.

description:
		@echo --------------------------------------------------------------------------------
		@echo $(HELP_MESSAGE)

# Double quotes are required for printing path reliably with raw mingw32-make (without MSYS shell).
path:
		@echo --------------------------------------------------------------------------------
		@echo PATH = "$(PATH)"

license:
		@echo Putting license...
		@$(foreach directory, $(INCLUDE_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(INCLUDE_FILE_TYPES) $(NATIVE_ORS) $(FIND); )
		@$(foreach directory, $(SOURCE_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(SOURCE_FILE_TYPES) $(NATIVE_ORS) $(FIND); )
		@$(foreach directory, $(CMAKE_DIRS), awkgward/makelic.sh $(LIC_HASH) hash $(directory) $(CMAKE_FILE_TYPES) $(NATIVE_ORS) $(FIND); )
		@$(foreach directory, $(QML_DIRS), awkgward/makelic.sh $(LIC_DSLASH) dslash $(directory) $(QML_FILE_TYPES) $(NATIVE_ORS) $(FIND); )

guards: | $(FIND) $(SH) $(AWK)
	    @echo Updating include guards...
		@$(FIND) $(INCLUDE_DIRS) \
		\( -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in' \) \
		-exec $(SH) awkgward/awkgward.sh $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(NATIVE_ORS) \;

doc: doc_doxygen

doc_doxygen: | $(FIND) $(SED) $(DOXYGEN)
		@$(FIND) $(DOXYGEN_INPUT_DIRS) \
		\( -name 'Doxyfile' -o -name '*.Doxyfile' \) \
		-execdir $(DOXYGEN) {} \;

doc_clean: | $(FIND)
		@$(FIND) $(DOXYGEN_OUTPUT_DIRS) -type f -delete

ports: | $(MAKE)
		$(MAKE) -C external/recipes/$(BUILD_MACHINE)

ports_clean: | $(MAKE)
		$(MAKE) -C external/recipes/$(BUILD_MACHINE) clean

ports_jobs:
		@echo Variable MAKE_BUILD_JOBS controls the number of parallel build jobs in recipes.
		@echo To alter the number of parallel build jobs either pass it as Make argument,
		@echo or override it in 'Makefile.user' file.
		@echo MAKE_BUILD_JOBS = $(MAKE_BUILD_JOBS)

