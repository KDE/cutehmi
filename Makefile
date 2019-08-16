# Copyright (c) 2018, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling, binging, yahooing or downloading it from pirate bay.
# NO WARRANTY.


first: help

# [help] Help message to be printed.

HELP_MESSAGE =

# [license] Names of files containing license text to be appended to files, commented out with double slash.
LICENSE_DSLASH = '*.LICENSE.dslash.inc'

# [license] Names of files containing license text to be appended to files, commented out with hash.
LICENSE_HASH = '*.LICENSE.hash.inc'

# [license] Names of files containing license text to be appended to files, commented out with XML comment.
LICENSE_XML = '*.LICENSE.xml.inc'

# [license] CMake file types.
CMAKE_FILE_TYPES = -name '*.cmake' -o -name 'CMakeLists.txt'

# [license] Qbs file types.
QBS_FILE_TYPES = -name '*.qbs'

# [license] QML file types.
QML_FILE_TYPES = -name '*.qml'

# [license] JavaScript file types.
JS_FILE_TYPES = -name '*.js'

# [license] XML file types.
XML_FILE_TYPES = -name '*.xml'

# [license] Source file types.
SOURCE_FILE_TYPES = -name '*.cpp' -o -name '*.c' -o -name '*.cpp.in'

# [license, guards] Include file types.
INCLUDE_FILE_TYPES = -name '*.hpp' -o -name '*.h' -o -name '*.hpp.in'

# [guards] A prefix used for include guards.
INCLUDE_GUARD_PREFIX = "AWKGWARD_"

# [doc_doxygen] List of Doxygen files.
DOC_DOXYGEN_FILES = 

# [doc_qdoc] List of qdoc files.
DOC_QDOC_FILES =

# [doc] Project-specific targets.
DOC_PROJECT_TARGETS = 

# [guards] Directories, where include guards should be updated.
INCLUDE_GUARDS_DIRS = $(INCLUDE_DIRS)

# [guards] Find expression that can be used to exclude some directories.
INCLUDE_GUARDS_EXCLUDE =

# [guards] Shell script that invokes 'awkgward.awk'.
AWKGWARD = awkgward/awkgward.sh

# [license_dslash] Directories, where licenses with double slash comments should be applied.
LICENSE_DSLASH_DIRS = /dev/null

# [license_dslash] File types for which licenses with double slash comments should be applied.
LICENSE_DSLASH_FILE_TYPES = $(INCLUDE_FILE_TYPES) -o $(SOURCE_FILE_TYPES) -o $(QML_FILE_TYPES) -o $(QBS_FILE_TYPES) -o $(JS_FILE_TYPES)

# [license_hash] Directories, where licenses with hash comments should be applied.
LICENSE_HASH_DIRS = /dev/null

# [license_hash] File types for which licenses with hash comments should be applied.
LICENSE_HASH_FILE_TYPES = $(CMAKE_FILE_TYPES)

# [license_xml] Directories, where licenses with XML comments should be applied.
LICENSE_XML_DIRS = /dev/null

# [license_xml] File types for which licenses with XML comments should be applied.
LICENSE_XML_FILE_TYPES = $(XML_FILE_TYPES)

# [license] Make license script.
MAKELIC = awkgward/makelic.sh


include Makefile.project


.PHONY: help description path license guards doc doc_clean doc_doxygen ports

help: description path
		@echo --------------------------------------------------------------------------------
		@echo Make targets are:
		@echo help - display this help box.
		@echo license[_dslash][_hash][_xml] - append license footer to files [comment style].
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

license: license_dslash license_hash license_xml

license_dslash: $(MAKELIC) $(LICENSE_DSLASH_DIRS) | $(FIND) $(SH) $(AWK) $(DIRNAME) $(MAKELIC) $(STAT) $(CUT) $(GREP) $(TOUCH) $(SED) $(ECHO) $(CAT) $(RM)
		@echo Applying licenses using double slash comment...
		@$(FIND) $(LICENSE_DSLASH_DIRS) -type f -name $(LICENSE_DSLASH) -exec $(SH) $(MAKELIC) {} dslash '$(LICENSE_DSLASH_FILE_TYPES)' $(NATIVE_IORS) $(FIND) \;

license_hash: $(MAKELIC) $(LICENSE_HASH_DIRS) | $(FIND) $(SH) $(AWK) $(DIRNAME) $(MAKELIC) $(STAT) $(CUT) $(GREP) $(TOUCH) $(SED) $(ECHO) $(CAT) $(RM)
		@echo Applying licenses using hash comment...
		@$(FIND) $(LICENSE_HASH_DIRS) -type f -name $(LICENSE_HASH) -exec $(SH) $(MAKELIC) {} hash '$(LICENSE_HASH_FILE_TYPES)' $(NATIVE_IORS) $(FIND) \;

license_xml: $(MAKELIC) $(LICENSE_XML_DIRS) | $(FIND) $(SH) $(AWK) $(DIRNAME) $(MAKELIC) $(STAT) $(CUT) $(GREP) $(TOUCH) $(SED) $(ECHO) $(CAT) $(RM)
		@echo Applying licenses using XML comment...
		@$(FIND) $(LICENSE_XML_DIRS) -type f -name $(LICENSE_XML) -exec $(SH) $(MAKELIC) {} xml '$(LICENSE_XML_FILE_TYPES)' $(NATIVE_IORS) $(FIND) \;

guards: $(AWKGWARD) $(INCLUDE_GUARDS_DIRS) | $(FIND) $(SH) $(AWK) $(CUT) $(GREP) $(TOUCH) $(STAT) $(AWK) $(ECHO) $(MV)
		@echo Updating include guards...
		@$(FIND) $(INCLUDE_GUARDS_DIRS) -type f \( $(INCLUDE_FILE_TYPES) \) $(INCLUDE_GUARDS_EXCLUDE) -exec $(SH) $(AWKGWARD) $(AWK) {} $(INCLUDE_GUARD_PREFIX) $(NATIVE_IORS) \;

doc: | $(MAKE)
		@$(MAKE) -C . doc_project_targets
		@$(MAKE) -C . doc_doxygen

doc_doxygen: | $(FIND) $(SED) $(DOXYGEN)
		@echo Doxygen path: "$(DOXYGEN)"
		@echo Doxygen version: $(shell $(DOXYGEN) -v)
		@$(FIND) $(DOXYGEN_INPUT_DIRS) \
		\( -name 'Doxyfile' -o -name '*.Doxyfile' \) \
		-execdir $(DOXYGEN) {} \;

doc_clean: | $(FIND)
		@$(FIND) $(DOXYGEN_OUTPUT_DIRS) -type f -delete

doc_project_targets: $(DOC_PROJECT_TARGETS)

ports: | $(MAKE)
		$(MAKE) -C external/recipes/$(BUILD_MACHINE)

ports_clean: | $(MAKE)
		$(MAKE) -C external/recipes/$(BUILD_MACHINE) clean

ports_jobs:
		@echo Variable MAKE_BUILD_JOBS controls the number of parallel build jobs in recipes.
		@echo To alter the number of parallel build jobs either pass it as Make argument,
		@echo or override it in 'Makefile.user' file.
		@echo MAKE_BUILD_JOBS = $(MAKE_BUILD_JOBS)

