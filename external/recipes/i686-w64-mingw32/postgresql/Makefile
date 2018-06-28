first: all

include ../Makefile.include

include ../libiconv/Makefile.include
include ../gettext/Makefile.include

include Makefile.include

PRODUCT_NAME = postgresql
PRODUCT_VERSION = 10.4
PRODUCT_DIRNAME = $(PRODUCT_NAME)-$(PRODUCT_VERSION)
PRODUCT_PORT_SUFFIX = $(TARGET_MACHINE)

PRODUCT_ARCHIVE = $(PRODUCT_NAME)-$(PRODUCT_VERSION).tar.gz
PRODUCT_ARCHIVE_URL = https://ftp.postgresql.org/pub/source/v10.4/$(PRODUCT_ARCHIVE)
PRODUCT_ARCHIVE_DIR = $(ARCHIVE_DIR)
PRODUCT_ARCHIVE_PATH = $(PRODUCT_ARCHIVE_DIR)/$(PRODUCT_ARCHIVE)

PRODUCT_SOURCE_DIR = $(SOURCE_DIR)/$(PRODUCT_DIRNAME)

PRODUCT_PORT_DIR = $(PORT_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_BUILD_DIR = $(BUILD_DIR)/$(PRODUCT_DIRNAME)-$(PRODUCT_PORT_SUFFIX)

PRODUCT_INSTALL_DIR = $(POSTGRESQL_INSTALL_DIR)
PRODUCT_INSTALL_INCLUDE_DIR = $(PRODUCT_INSTALL_DIR)/include
PRODUCT_INSTALL_LIB_DIR = $(PRODUCT_INSTALL_DIR)/bin

PRODUCT_DEPLOY_DIR = $(POSTGRESQL_DEPLOY_DIR)
PRODUCT_DEPLOY_INCLUDE_DIR = $(PRODUCT_DEPLOY_DIR)/include
PRODUCT_DEPLOY_LIB_DIR = $(PRODUCT_DEPLOY_DIR)/lib

PRODUCT_CONFIGURE_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).configure.txt 
PRODUCT_README_PORT_MD_PATH = $(PRODUCT_PORT_DIR)/README.$(PRODUCT_PORT_SUFFIX).md
PRODUCT_BUILD_TXT_PATH = $(BUILD_DIR)/$(PRODUCT_NAME)-$(PRODUCT_VERSION)-$(PRODUCT_PORT_SUFFIX).build.txt

PRODUCT_INCLUDE_FILES = libpq server informix internal ecpg_config.h ecpg_informix.h ecpgerrno.h ecpglib.h ecpgtype.h libpq-events.h libpq-fe.h pg_config.h pg_config_ext.h pg_config_manual.h pg_config_os.h pgtypes_date.h pgtypes_error.h pgtypes_interval.h pgtypes_numeric.h pgtypes_timestamp.h postgres_ext.h sql3types.h sqlca.h sqlda-compat.h sqlda-native.h sqlda.h
PRODUCT_INCLUDE_FILES_INSTALL := $(addprefix $(PRODUCT_INSTALL_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))
PRODUCT_INCLUDE_FILES_DEPLOY := $(addprefix $(PRODUCT_DEPLOY_INCLUDE_DIR)/, $(PRODUCT_INCLUDE_FILES))

PRODUCT_LIB_FILES = libpq.dll
PRODUCT_LIB_FILES_INSTALL = $(addprefix $(PRODUCT_INSTALL_LIB_DIR)/, $(PRODUCT_LIB_FILES))
PRODUCT_LIB_FILES_DEPLOY = $(addprefix $(PRODUCT_DEPLOY_LIB_DIR)/, $(PRODUCT_LIB_FILES))

PATH := $(GETTEXT_INSTALL_DIR)/bin:$(LIBICONV_INSTALL_DIR)/bin:$(PATH)

export PATH MAKE

include ../Makefile.phony

all: deploy

include ../Makefile.deploy

# Parallel install of gettext seems to cause conflicting access to some files, so force a single job.
buildinstall $(PRODUCT_LIB_FILES_INSTALL) $(PRODUCT_INCLUDE_FILES_INSTALL): $(PRODUCT_BUILD_TXT_PATH) | $(CD) $(MAKE)
	$(CD) $(PRODUCT_BUILD_DIR) && $(MAKE) -j 1 install

build $(PRODUCT_BUILD_TXT_PATH): $(PRODUCT_BUILD_DIR)/GNUmakefile | $(CD) $(MAKE) $(TEE) $(CMD) $(PERL)
	$(CD) $(PRODUCT_BUILD_DIR) && $(MAKE) -j $(MAKE_BUILD_JOBS) 2>&1 | $(TEE) $(PRODUCT_BUILD_TXT_PATH)

buildconfigure $(PRODUCT_BUILD_DIR)/GNUmakefile: $(PRODUCT_BUILD_DIR)/configure \
		$(LIBICONV_INSTALL_DIR) \
		$(GETTEXT_INSTALL_DIR) | $(CD) $(SH) $(TEE) $(AWK) $(SED) $(CMD) $(PERL)
	$(CD) $(PRODUCT_BUILD_DIR) && $(SH) configure --host=$(HOST_MACHINE) --build=$(BUILD_MACHINE) \
		--prefix=$(PRODUCT_INSTALL_DIR) \
		--sysconfdir=/etc \
		--localedir=/share/locale \
		--enable-nls \
		--with-libraries=$(LIBICONV_INSTALL_DIR)/lib:$(GETTEXT_INSTALL_DIR)/lib \
		--with-includes=$(LIBICONV_INSTALL_DIR)/include:$(GETTEXT_INSTALL_DIR)/include \
		--disable-rpath \
		2>&1 | $(TEE) $(PRODUCT_CONFIGURE_TXT_PATH)

include ../Makefile.builddir

include ../Makefile.port

include ../Makefile.portdir

include ../Makefile.sourcedir

include ../Makefile.archive

include ../Makefile.clean

