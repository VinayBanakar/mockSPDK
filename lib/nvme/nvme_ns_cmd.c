#include "nvme_internal.h"
#include <fcntl.h>
#include <stdio.h>

struct driveState {
  bool fileCreated;
  int ffd;
  size_t fileSize;
};

struct driveState *smd;
int drive_block_size = 512;
unsigned long int mock_file_size = 20000 * 1024*1024L; //16 GB file
char *mockFile = "/fastdisk/mockDrive";
// creates mock drive and initializes driveState
int init_mockDrive(size_t fileSize){

    //struct driveState md = { .fileCreated=false, .fileSize = 0, .ffd = 0};
    smd = malloc(sizeof (struct driveState)); // free this in cleanup method
    smd->fileCreated=false;
    smd->fileSize=0;
    smd->ffd=0;
    if(smd == NULL){ return 1; }
    int fd = open(mockFile, O_RDWR|O_CREAT, 0666);
    if (fd < 0) return 1;
    //if(posix_fallocate(fd, 0, fileSize)==0){
    if(fallocate(fd,FALLOC_FL_KEEP_SIZE||FALLOC_FL_PUNCH_HOLE, 0, fileSize)==0){ //ext4 only
      smd->fileCreated = true;
      smd->ffd = fd;
      smd->fileSize = fileSize;
      return 0;
    }
    return 1;
}

int spdk_nvme_ns_cmd_read(struct spdk_nvme_ns *ns,
                          struct spdk_nvme_qpair *qpair, void *buffer,
                          uint64_t lba, uint32_t lba_count,
                          spdk_nvme_cmd_cb cb_fn, void *cb_arg,
                          uint32_t io_flags) {
  //block number is essentially offset in a file
  if(smd == NULL || !smd->fileCreated){
     printf("Mock file not open.\n");
     if( access( mockFile, F_OK ) != -1 ) {
       // exists
       if(init_mockDrive(mock_file_size) != 0){
          printf("File open or falloc failed\n"); 
          return 1;
       }
     } else {
        printf("File doesn't exist --write-zeros\n");
        return 1;
     }
   }
   if(smd->ffd > 0){
      int val = pread(smd->ffd, buffer, lba_count*drive_block_size, lba);
      if(val<0){
        printf("Read failed.\n");
        return 1;
      }
      (*cb_fn)(cb_arg,NULL);
   }

  return 0;
}

int spdk_nvme_ns_cmd_write(struct spdk_nvme_ns *ns,
                           struct spdk_nvme_qpair *qpair, void *buffer,
                           uint64_t lba, uint32_t lba_count,
                           spdk_nvme_cmd_cb cb_fn, void *cb_arg,
                           uint32_t io_flags) {
  if(smd == NULL || !smd->fileCreated){
    size_t fileSize = mock_file_size;
    if(init_mockDrive(fileSize) != 0){
      printf("File creation or falloc failed\n"); 
      return 1;
    } else {
      if (smd->ffd > 0) {
        //printf("%d\n", smd->fileCreated);
        printf("New file of size %ld is created.\n", smd->fileSize);
      } else {
        printf("File created but not open\n");
      }
    }
  }
  // maybe pass the block number in cb_arg?
  int val = pwrite(smd->ffd, buffer, lba_count*drive_block_size, lba);
  //use fwrite since buffer may not be null terminated?
  if (val>=0){
    // just call the call back if write succeeds
    (*cb_fn)(cb_arg,NULL);
  }
  return 0;
}

int spdk_nvme_ns_cmd_write_zeroes(struct spdk_nvme_ns *ns,
                                  struct spdk_nvme_qpair *qpair, uint64_t lba,
                                  uint32_t lba_count, spdk_nvme_cmd_cb cb_fn,
                                  void *cb_arg, uint32_t io_flags) {
  if(smd == NULL || !smd->fileCreated){
     printf("Mock file not open.\n");
     if( access( mockFile, F_OK ) != -1 ) {
       // exists
       if(init_mockDrive(mock_file_size) != 0){
          printf("File open or falloc failed\n"); 
          return 1;
       }
     } else {
        printf("File doesn't exist --write-zeros\n");
        return 1;
     }
   }
   int arr_size = lba_count * drive_block_size;
   char zero_array[arr_size];
   memset(zero_array, 0, arr_size); // might overflow here.
   if(smd->ffd > 0){
    int val = pwrite(smd->ffd, zero_array, arr_size, lba);
    if (val>=0){
    // just call the call back if write succeeds
    (*cb_fn)(cb_arg,NULL);
    }
   }
  return 0;
}

int
spdk_nvme_ns_cmd_flush(struct spdk_nvme_ns *ns, struct spdk_nvme_qpair *qpair,
		       spdk_nvme_cmd_cb cb_fn, void *cb_arg)
{
    if(smd != NULL){
      int ret =fflush(smd->ffd);
      if(ret!=0){
        printf("Fflush failed.\n");
        return 1;
      }
      //invoke call back
      (*cb_fn)(cb_arg,NULL);
  }
  return 0;
}