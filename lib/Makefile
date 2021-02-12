SPDK_ROOT_DIR := $(abspath $(CURDIR)/..)
include $(SPDK_ROOT_DIR)/mk/spdk.common.mk

DIRS-y += nvme env_dpdk util
#ifeq($(OS), Linux)

#DIRS - $(CONFIG_VHOST) += vhost
#DIRS - $(CONFIG_VIRTIO) += virtio
#endif

.PHONY: all clean $(DIRS-y)

all: $(DIRS-y)
clean: $(DIRS-y)

include $(SPDK_ROOT_DIR)/mk/spdk.subdirs.mk
