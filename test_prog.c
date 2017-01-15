#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  size_t maxlen = 256;

  if (argc < 4) {
    fprintf(stderr, "%s [s1] [s2] [flags] compare string s1 against string s2 (maximum 256 bytes long per strings.)\n \
flags can be 0 or LS_ICASE only.\n\n",
	    argv[0]);
    return -1;
  }

  printf("Returned: %d\n\n", s_strcmp(argv[1], argv[2], maxlen, atoi(argv[3])));
    
  
  return 0;
}
