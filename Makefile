# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling, binging, yahooing or downloading it from pirate bay.
# NO WARRANTY.


first: help

# [help] Help message to be printed.

HELP_MESSAGE =

# [license] Names of files containing license text to be appended to files, commented out with double slash.
LIC_DSLASH = *.LICENSE.dslash.inc

# [license] Names of files containing license text to be appended to files, commented out with hash.
LIC_HASH = *.LICENSE.hash.inc

# [license] Names of files containing license text to be appended to files, commented out with XML comment.
LIC_XML = *.LICENSE.xml.inc

# [license] Directories containing CMake files.
CMAKE_DIRS =

# [license] CMake file types.
CMAKE_FILE_TYPES = -name '*.cmake' -o -name 'CMakeLists.txt'

# [license] Directories containing qbs files.
QBS_DIRS = 

# [license] Qbs file types.
QBS_FILE_TYPES = -name '*.qbs'

# [license] Directories containing QML files.
QML_DIRS =

# [license] QML file types.
QML_FILE_TYPES = -name '*.qml'

# [license] Directories containing JavaScript files.
JS_DIRS = 

# [license] JavaScript file types.
JS_FILE_TYPES = -name '*.js'

# [license] XML file types.
XML_FILE_TYPES = -name '*.xml'

# [license] Directories containing XML files.
XML_DIRS = 

# [license, sources] Directories containing source files.
SOURCE_DIRS =

# [license] Source file types.
SOURCE_FILE_TYPES = -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in'

# [license, guards] Directories containing header files.
INCLUDE_DIRS =

# [license, guards] Include file types.
INCLUDE_FILE_TYPES = -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in'

# [guards] A prefix used for include guards.
INCLUDE_GUARD_PREFIX = "AWKGWARD_"

# [doc_doxygen] List of Doxygen files.
DOC_DOXYGEN_FILES = 

# [doc_qdoc] List of qdoc files.
DOC_QDOC_FILES =

# [license] Make license script.
MAKELIC = awkgward/makelic.sh


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
		@echo --------------------------------------------------------------------------------
		@echo Note: you can create Makefile.user file to override Make variables.

description:
		@echo --------------------------------------------------------------------------------
		@echo $(HELP_MESSAGE)

# Double quotes are required for printing path reliably with raw mingw32-make (without MSYS shell).
path:
		@echo --------------------------------------------------------------------------------
		@echo PATH = "$(PATH)"

license: | $(FIND) $(SH) $(AWK) $(DIRNAME) $(MAKELIC) $(STAT) $(CUT) $(GREP) $(TOUCH) $(SED) $(ECHO) $(CAT) $(RM)
		@echo Putting license...
		@$(FIND) $(INCLUDE_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(INCLUDE_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(SOURCE_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(SOURCE_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(QML_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(QML_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(QBS_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(QBS_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(QBS_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(QBS_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(JS_DIRS) -type f -name $(LIC_DSLASH) -exec $(SH) -c '$(MAKELIC) {} dslash "$(JS_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;
		@$(FIND) $(XML_DIRS) -type f -name $(LIC_XML) -exec $(SH) -c '$(MAKELIC) {} xml "$(XML_FILE_TYPES)" $(NATIVE_IORS) $(FIND)' \;

guards: awkgward/awkgward.sh | $(FIND) $(SH) $(AWK) $(CUT) $(GREP) $(TOUCH) $(STAT) $(AWK) $(ECHO) $(MV)
	    @echo Updating include guards...
		@$(FIND) $(INCLUDE_DIRS) -type f \( $(INCLUDE_FILE_TYPES) \) -exec $(SH) awkgward/awkgward.sh $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(NATIVE_IORS) \;

doc: doc_doxygen

doc_doxygen: | $(FIND) $(SED) $(DOXYGEN)
		@echo Doxygen path: "$(DOXYGEN)"
		@echo Doxygen version: $(shell $(DOXYGEN) -v)
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

