#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  kpgtbl();
  sbrk(1);
  printf("After calling sbrk(1)\n");
  // It seems we get an extra page...
  kpgtbl();
  exit(0);
}
