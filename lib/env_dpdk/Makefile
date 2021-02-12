SPDK_ROOT_DIR := $(abspath $(CURDIR)/../..)
include $(SPDK_ROOT_DIR)/mk/spdk.common.mk

CFLAGS += $(ENV_CFLAGS)
C_SRCS = env.c init.c 
LIBNAME = env_dpdk

include $(SPDK_ROOT_DIR)/mk/spdk.lib.mk
