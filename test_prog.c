#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  int ret = 0;
  size_t len1 = 0, len2 = 0;
  


  if (argc < 4) {
    fprintf(stderr, "\n%s [s1] [s2] [flags]\n\nCompare s1 against s2, returning smaller than, equal to or bigger than 0\
 if s1 is smaller than, equal to or bigger than s2\nflags are a bitwise OR of the following constant:\n\n\
1: Case insensitive comparaison\n2: Spaces and underscores are treated to be the same character.\n\n", argv[0]);
    return -1;
  }
  len1 = strlen(argv[1]);
  len2 = strlen(argv[2]);
  ret = s_strcmp(argv[1], argv[2],
		 strlen(argv[2]),
		 atoi(argv[3]));
  printf("Result: %d\n\n", ret);
  
  return 0;
}
