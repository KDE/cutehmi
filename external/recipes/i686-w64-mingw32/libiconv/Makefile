first: all

include ../Makefile.include
include Makefile.include

PRODUCT_NAME = libiconv
PRODUCT_VERSION = 1.15
PRODUCT_DIRNAME = $(PRODUCT_NAME)-$(PRODUCT_VERSION)
PRODUCT_PORT_SUFFIX = $(TARGET_MACHINE)

PRODUCT_ARCHIVE = $(PRODUCT_NAME)-$(PRODUCT_VERSION).tar.gz
PRODUCT_ARCHIVE_URL = ftp://ftp.gnu.org/pub/gnu/libiconv/$(PRODUCT_ARCHIVE)
PRODUCT_ARCHIVE_DIR = $(ARCHIVE_DIR)
PRODUCT_ARCHIVE_PATH = $(PRODUCT_ARCHIVE_DIR)/$(PRODUCT_ARCHIVE)

PRODUCT_SOURCE_DIR = $(SOURCE_DIR)/$(PRODUCT_DIRNAME)

PRODUCT_PORT_DIR = $(PORT_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_BUILD_DIR = $(BUILD_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_INSTALL_DIR = $(LIBICONV_INSTALL_DIR)
PRODUCT_INSTALL_INCLUDE_DIR = $(PRODUCT_INSTALL_DIR)/include
PRODUCT_INSTALL_LIB_DIR = $(PRODUCT_INSTALL_DIR)/bin

PRODUCT_DEPLOY_DIR = $(LIBICONV_DEPLOY_DIR)
PRODUCT_DEPLOY_INCLUDE_DIR = $(PRODUCT_DEPLOY_DIR)/include
PRODUCT_DEPLOY_LIB_DIR = $(PRODUCT_DEPLOY_DIR)/lib

PRODUCT_CONFIGURE_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).configure.txt 
PRODUCT_README_PORT_MD_PATH = $(PRODUCT_PORT_DIR)/README.$(PRODUCT_PORT_SUFFIX).md
PRODUCT_BUILD_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).build.txt

PRODUCT_INCLUDE_FILES = iconv.h
PRODUCT_INCLUDE_FILES_INSTALL = $(addprefix $(PRODUCT_INSTALL_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))
PRODUCT_INCLUDE_FILES_DEPLOY = $(addprefix $(PRODUCT_DEPLOY_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))

PRODUCT_LIB_FILES = libiconv-2.dll
PRODUCT_LIB_FILES_INSTALL = $(addprefix $(PRODUCT_INSTALL_LIB_DIR)/, $(PRODUCT_LIB_FILES))
PRODUCT_LIB_FILES_DEPLOY = $(addprefix $(PRODUCT_DEPLOY_LIB_DIR)/, $(PRODUCT_LIB_FILES))

export PATH MAKE

include ../Makefile.phony

all: deploy

include ../Makefile.deploy

include ../Makefile.buildinstall

build $(PRODUCT_BUILD_TXT_PATH): $(PRODUCT_BUILD_DIR)/Makefile | $(CD) $(MAKE) $(TEE) $(CMD)
	$(CD) $(PRODUCT_BUILD_DIR) && $(MAKE) -j $(MAKE_BUILD_JOBS) CFLAGS+='-g0' 2>&1 | $(TEE) $(PRODUCT_BUILD_TXT_PATH)

buildconfigure $(PRODUCT_BUILD_DIR)/Makefile: $(PRODUCT_BUILD_DIR)/configure | $(CD) $(SH) $(TEE) $(AWK) $(SED) $(CMD)
	$(CD) $(PRODUCT_BUILD_DIR) && $(SH) configure --host=$(HOST_MACHINE) --build=$(BUILD_MACHINE) \
		--enable-relocatable \
		--prefix=$(PRODUCT_INSTALL_DIR) \
		--without-libiconv-prefix \
		--without-libintl-prefix \
		--disable-nls --disable-rpath \
		2>&1 | $(TEE) $(PRODUCT_CONFIGURE_TXT_PATH)

include ../Makefile.builddir

port $(PRODUCT_README_PORT_MD_PATH): README.md $(PRODUCT_PORT_DIR) | $(PATCH) $(CP) $(TOUCH)
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0001-Update-from-gnulib.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0002-Get-rid-of-autom4te.cache-directories-as-far-as-poss.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0003-Don-t-attempt-to-build-preloadable_libiconv.so-when-.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0004-Allow-building-statically-linked-binaries-through-LD.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0005-Avoid-end-of-lines-problem-in-generated-shell-script.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0006-Fix-installation-in-64-bit-mode-on-AIX.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0007-Don-t-use-an-undocumented-Autoconf-macro.patch
	$(PATCH) -d $(PRODUCT_PORT_DIR) -p1 < 0008-Rename-some-files.patch
	$(CP) README.md $(PRODUCT_README_PORT_MD_PATH)
	$(TOUCH) $(PRODUCT_README_PORT_MD_PATH)

include ../Makefile.portdir

include ../Makefile.sourcedir

include ../Makefile.archive

include ../Makefile.clean

