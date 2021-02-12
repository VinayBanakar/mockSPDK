#include "nvme_internal.h"

bool spdk_nvme_ns_is_active(struct spdk_nvme_ns *ns) { return true; }

uint32_t spdk_nvme_ns_get_id(struct spdk_nvme_ns *ns) {
  return ns->id;
}

uint32_t spdk_nvme_ns_get_flags(struct spdk_nvme_ns *ns) {
  return ns->flags;
}

uint32_t spdk_nvme_ns_get_sector_size(struct spdk_nvme_ns *ns) {
  return ns->sector_size;
}

uint64_t spdk_nvme_ns_get_size(struct spdk_nvme_ns *ns) {
  uint64_t bytes = 214000000000;
  return bytes;
}