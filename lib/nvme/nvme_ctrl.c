#include "nvme_internal.h"
#include "spdk/env.h"
#include "spdk/stdinc.h"
#include "spdk/string.h"

struct spdk_nvme_qpair g_qpair;

const struct spdk_nvme_ctrlr_data *spdk_nvme_ctrlr_get_data(
    struct spdk_nvme_ctrlr *ctrlr) {

  return &ctrlr->cdata;
}

struct spdk_nvme_ns *spdk_nvme_ctrlr_get_ns(struct spdk_nvme_ctrlr *ctrlr,
                                            uint32_t nsid) {
	if (nsid < 1 || nsid > ctrlr->num_ns) {
		return NULL;
	}

	return &ctrlr->ns[nsid - 1];
}

uint32_t spdk_nvme_ctrlr_get_num_ns(struct spdk_nvme_ctrlr *ctrlr) {
  return ctrlr->num_ns;
}

// not using qpairs at the moment.
struct spdk_nvme_qpair *spdk_nvme_ctrlr_alloc_io_qpair(
  struct spdk_nvme_ctrlr *ctrlr,
  const struct spdk_nvme_io_qpair_opts *user_opts, size_t opts_size) {
  g_qpair.id=0;
  g_qpair.qprio=0;
  g_qpair.ctrlr=ctrlr;
  return &g_qpair;
}

int spdk_nvme_ctrlr_free_io_qpair(struct spdk_nvme_qpair *qpair) { return 0; }


// Should return pointer to a buffer.
void *
spdk_nvme_ctrlr_alloc_cmb_io_buffer(struct spdk_nvme_ctrlr *ctrlr, size_t size)
{
	void *buf;

	// if (size == 0) {
	// 	return NULL;
	// }

	// nvme_robust_mutex_lock(&ctrlr->ctrlr_lock);
	// buf = nvme_transport_ctrlr_alloc_cmb_io_buffer(ctrlr, size);
	// nvme_robust_mutex_unlock(&ctrlr->ctrlr_lock);
	buf = malloc(size * sizeof(char));
	// return buf;

  return buf;
}

void
spdk_nvme_ctrlr_free_cmb_io_buffer(struct spdk_nvme_ctrlr *ctrlr, void *buf, size_t size)
{
	free(buf);
	// if (buf && size) {
	// 	nvme_robust_mutex_lock(&ctrlr->ctrlr_lock);
	// 	nvme_transport_ctrlr_free_cmb_io_buffer(ctrlr, buf, size);
	// 	nvme_robust_mutex_unlock(&ctrlr->ctrlr_lock);
	// }
}
