#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#incude <fcntl.h>

#define AM33XX

#include "pwm.h"

void main(int argc, char** argv) {
  int dev_mem_fd;

  int value = atoi(argv[1]);

  printf("VALUE IS %d\r\n",value);

  dev_mem_fd = open ("/dev/mem", O_RDWR | O_SYNC);
  if (dev_mem_fd == -1) {
    perror ("open failed");
    assert(0);
  }
  void *mapped = mmap(NULL, EPWM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, dev_mem_fd, EPWM2_BASE);
  if (mapped == (volatile uint32_t *)MAP_FAILED) {
    perror("mmap failed");
    close(dev_mem_fd);
    assert(0);
  }
  munmap(mapped, EPWM_SIZE);
  close(dev_mem_fd);
}
