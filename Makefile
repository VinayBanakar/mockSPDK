S :=

SPDK_ROOT_DIR := $(CURDIR)
include $(SPDK_ROOT_DIR)/mk/spdk.common.mk

DIRS-y += lib include examples
#DIRS-$(CONFIG_TESTS) += test

.PHONY: all clean $(DIRS-y) config.h CONFIG.local mk/cc.mk cc_version cxx_version

ifeq ($(CURDIR)/dpdk/build,$(CONFIG_DPDK_DIR))
ifneq ($(SKIP_DPDK_BUILD),1)
DPDKBUILD = dpdkbuild
DIRS-y += dpdkbuild
endif
endif

all: $(DIRS-y)
clean: $(DIRS-y)
	$(Q)rm -f mk/cc.mk
	$(Q)rm -f config.h

install: all
	$(Q)echo "Installed to $(DESTDIR)$(CONFIG_PREFIX)"

lib: $(DPDKBUILD)
#app: lib
#test: lib
#examples: lib
pkgdep:
	sh ./scripts/pkgdep.sh

#$(DIRS-y): mk/cc.mk config.h
$(DIRS-y): mk/cc.mk
mk/cc.mk:
	$(Q)scripts/detect_cc.sh --cc=$(CC) --cxx=$(CXX) --lto=$(CONFIG_LTO) > $@.tmp; \
	cmp -s $@.tmp $@ || mv $@.tmp $@ ; \
 	rm -f $@.tmp

# config.h: CONFIG CONFIG.local scripts/genconfig.py
# 	$(Q)PYCMD=$$(cat PYTHON_COMMAND 2>/dev/null) ; \
# 	test -z "$$PYCMD" && PYCMD=python ; \
# 	$$PYCMD scripts/genconfig.py $(MAKEFLAGS) > $@.tmp; \
# 	cmp -s $@.tmp $@ || mv $@.tmp $@ ; \
# 	rm -f $@.tmp

cc_version: mk/cc.mk
	$(Q)echo "SPDK using CC=$(CC)"; $(CC) -v

cxx_version: mk/cc.mk
	$(Q)echo "SPDK using CXX=$(CXX)"; $(CXX) -v

include $(SPDK_ROOT_DIR)/mk/spdk.subdirs.mk
