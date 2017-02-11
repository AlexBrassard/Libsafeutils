#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  if (argc < 4) {
    fprintf(stderr, "%s: [haystack] [needle] [flags]\n\n", argv[0]);
    return -1;
  }
  printf("Haystack: %s\nNeedle: %s\nMatch: %d\n\n",
	 argv[1], argv[2], s_strstr(argv[1], argv[2], 256, atoi(argv[3])));

  return 0;
}
