#include "nvme_internal.h"
#include "spdk/nvmf_spec.h"

struct spdk_nvme_transport_id trod = {0};
struct spdk_nvme_ctrlr ctrlr;
struct spdk_nvme_ns *ns;

int spdk_nvme_probe(const struct spdk_nvme_transport_id *trid, void *cb_ctx,
                    spdk_nvme_probe_cb probe_cb, spdk_nvme_attach_cb attach_cb,
                    spdk_nvme_remove_cb remove_cb) {

  struct spdk_nvme_transport_id *tr = &trod;
  tr->trtype = SPDK_NVME_TRANSPORT_PCIE;
  char serial_id[] = "0000:00:04.2";
	memcpy(tr->traddr,serial_id,strlen(serial_id)+1);
  ctrlr.trid = *tr;
  ctrlr.num_ns = 1;

  struct spdk_nvme_ns ns_t = { .ctrlr = &ctrlr, .sector_size = 512, .extended_lba_size = 512, .md_size = 0, .pi_type = 0, .sectors_per_max_io = 4048, .sectors_per_stripe = 0, .id = 1, .flags = 10};
  ns = &ns_t;
  ctrlr.ns = ns;

    struct spdk_nvme_ctrlr_data mockCdata = {
	  .vid = 32902,
	  .ssvid = 6900,
	  .sn = "serial0",
	  .mn = "Mock NVMe Ctrl"
  };
  ctrlr.cdata = mockCdata;

  (*probe_cb)(cb_ctx, tr, NULL);
  (*attach_cb)(cb_ctx, tr, &ctrlr, NULL);
  return 0;
}

int spdk_nvme_detach(struct spdk_nvme_ctrlr *ctrlr) { return 0; }