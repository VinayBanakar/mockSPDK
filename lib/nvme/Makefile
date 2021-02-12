SPDK_ROOT_DIR := $(abspath $(CURDIR)/../..)
include $(SPDK_ROOT_DIR)/mk/spdk.common.mk

C_SRCS = nvme.c nvme_ctrl.c nvme_ns.c nvme_ns_cmd.c nvme_qpair.c
LIBNAME = nvme

include $(SPDK_ROOT_DIR)/mk/spdk.lib.mk
