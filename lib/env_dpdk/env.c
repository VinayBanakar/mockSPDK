#include "spdk/env.h"

#include "spdk/stdinc.h"

void *spdk_dma_malloc(size_t size, size_t align, uint64_t *phys_addr) {
  void* buf = malloc(size);
  if(buf) {
    memset(buf, 0, size);
  }
  return buf;
}

void spdk_dma_free(void *buf) {
  free(buf);
}

void *
spdk_dma_zmalloc(size_t size, size_t align, uint64_t *phys_addr)
{
  void* buf = malloc(size);
  if(buf) {
    memset(buf, 0, size);
  }
  return buf;
}