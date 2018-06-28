first: all

include ../Makefile.include

include ../libiconv/Makefile.include

include Makefile.include

PRODUCT_NAME = gettext
PRODUCT_VERSION = 0.19.8.1
PRODUCT_DIRNAME = $(PRODUCT_NAME)-$(PRODUCT_VERSION)
PRODUCT_PORT_SUFFIX = $(TARGET_MACHINE)

PRODUCT_ARCHIVE = $(PRODUCT_NAME)-$(PRODUCT_VERSION).tar.gz
PRODUCT_ARCHIVE_URL = ftp://ftp.gnu.org/pub/gnu/gettext/$(PRODUCT_ARCHIVE)
PRODUCT_ARCHIVE_DIR = $(ARCHIVE_DIR)
PRODUCT_ARCHIVE_PATH = $(PRODUCT_ARCHIVE_DIR)/$(PRODUCT_ARCHIVE)

PRODUCT_SOURCE_DIR = $(SOURCE_DIR)/$(PRODUCT_DIRNAME)

PRODUCT_PORT_DIR = $(PORT_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_BUILD_DIR = $(BUILD_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_INSTALL_DIR = $(GETTEXT_INSTALL_DIR)
PRODUCT_INSTALL_INCLUDE_DIR = $(PRODUCT_INSTALL_DIR)/include
PRODUCT_INSTALL_LIB_DIR = $(PRODUCT_INSTALL_DIR)/bin

PRODUCT_DEPLOY_DIR = $(GETTEXT_DEPLOY_DIR)
PRODUCT_DEPLOY_INCLUDE_DIR = $(PRODUCT_DEPLOY_DIR)/include
PRODUCT_DEPLOY_LIB_DIR = $(PRODUCT_DEPLOY_DIR)/lib

PRODUCT_CONFIGURE_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).configure.txt 
PRODUCT_README_PORT_MD_PATH = $(PRODUCT_PORT_DIR)/README.$(PRODUCT_PORT_SUFFIX).md
PRODUCT_BUILD_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).build.txt

PRODUCT_INCLUDE_FILES = autosprintf.h  gettext-po.h  libintl.h
PRODUCT_INCLUDE_FILES_INSTALL = $(addprefix $(PRODUCT_INSTALL_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))
PRODUCT_INCLUDE_FILES_DEPLOY = $(addprefix $(PRODUCT_DEPLOY_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))

PRODUCT_LIB_FILES = libintl-8.dll 
PRODUCT_LIB_FILES_INSTALL = $(addprefix $(PRODUCT_INSTALL_LIB_DIR)/, $(PRODUCT_LIB_FILES))
PRODUCT_LIB_FILES_DEPLOY = $(addprefix $(PRODUCT_DEPLOY_LIB_DIR)/, $(PRODUCT_LIB_FILES))

PATH := $(LIBICONV_INSTALL_DIR)/bin:$(PATH)

export PATH MAKE

include ../Makefile.phony

all: deploy

include ../Makefile.deploy

# Parallel install of gettext seems to cause conflicting access to some files, so force a single job.
buildinstall $(PRODUCT_LIB_FILES_INSTALL) $(PRODUCT_INCLUDE_FILES_INSTALL): $(PRODUCT_BUILD_TXT_PATH) | $(CD) $(MAKE)
	$(CD) $(PRODUCT_BUILD_DIR) && $(MAKE) -j 1 install

build $(PRODUCT_BUILD_TXT_PATH): $(PRODUCT_BUILD_DIR)/Makefile | $(CD) $(MAKE) $(TEE) $(CMD)
	$(CD) $(PRODUCT_BUILD_DIR) && $(MAKE) -j $(MAKE_BUILD_JOBS) CFLAGS+='-g0' 2>&1 | $(TEE) $(PRODUCT_BUILD_TXT_PATH)

buildconfigure $(PRODUCT_BUILD_DIR)/Makefile: $(PRODUCT_BUILD_DIR)/configure \
		$(LIBICONV_INSTALL_DIR) | $(CD) $(SH) $(TEE) $(AWK) $(SED) $(CMD)
	$(CD) $(PRODUCT_BUILD_DIR) && $(SH) configure --host=$(HOST_MACHINE) --build=$(BUILD_MACHINE) \
		--enable-relocatable \
		--prefix=$(PRODUCT_INSTALL_DIR) \
		--with-libiconv-prefix=$(LIBICONV_INSTALL_DIR) \
		--disable-rpath \
		2>&1 | $(TEE) $(PRODUCT_CONFIGURE_TXT_PATH)

include ../Makefile.builddir

port $(PRODUCT_README_PORT_MD_PATH): README.md $(PRODUCT_PORT_DIR) | $(PATCH) $(CP) $(TOUCH)
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0001-fix-msginit.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0002-add-GETTEXTIOENCODING-support.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0003-move-cldr-plurals.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 -Z < 0004-fix-gl_cv_prog_as_underscore-test.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0005-improve-plural-rules-detection.patch
	$(CP) README.md $(PRODUCT_README_PORT_MD_PATH)
	$(TOUCH) $(PRODUCT_README_PORT_MD_PATH)

include ../Makefile.portdir

include ../Makefile.sourcedir

include ../Makefile.archive

include ../Makefile.clean

