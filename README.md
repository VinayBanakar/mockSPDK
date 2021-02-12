```
Do SPDK development without access to NVMe SSD using MockSPDK.  
MockSPDK uses a file to substitute your drive.  

At this point many of the APIs are not complete but you can run `hello_world` from `examples`.
```
```bash
sudo mockSpdk/scripts/pkgdep.sh
#git submodule update --init
mkdir -p build/lib
make
make -f Makefile.sharedlib
```

API
```
spdk_env_opts_init
spdk_env_init
spdk_nvme_probe
spdk_dma_malloc
spdk_dma_free
spdk_dma_zmalloc
spdk_nvme_ns_is_active
spdk_nvme_ns_get_id
spdk_nvme_ns_get_flags
spdk_nvme_ns_get_sector_size
spdk_nvme_ns_get_size
spdk_nvme_ns_cmd_read
spdk_nvme_ns_cmd_write
spdk_nvme_ns_cmd_write_zeroes
spdk_nvme_ns_cmd_flush
spdk_nvme_ctrlr_get_data
spdk_nvme_ctrlr_get_ns
spdk_nvme_ctrlr_get_num_ns
spdk_nvme_ctrlr_alloc_io_qpair
spdk_nvme_ctrlr_free_io_qpair
spdk_nvme_qpair_process_completions
spdk_nvme_detach
```

