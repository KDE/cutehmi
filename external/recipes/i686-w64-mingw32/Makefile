first: all

include $(dir $(abspath $(lastword $(MAKEFILE_LIST))))Makefile.include

export PATH MAKE

.PHONY: all clean mostlyclean

.NOTPARALLEL: all

all: | $(MAKE)
	$(MAKE) -C libiconv
	$(MAKE) -C gettext
	$(MAKE) -C libgpg-error
	$(MAKE) -C libgcrypt
	$(MAKE) -C zlib
	$(MAKE) -C libssh
	$(MAKE) -C postgresql

clean: mostlyclean | $(RM)
	$(RM) -Rf $(SOURCE_DIR)
	$(RM) -Rf $(ARCHIVE_DIR)

mostlyclean: deployclean | $(RM)
	$(RM) -Rf $(INSTALL_DIR)
	$(RM) -Rf $(BUILD_DIR)
	$(RM) -Rf $(PORT_DIR)

deployclean: | $(RM)
	$(RM) -Rf $(DEPLOY_DIR)

