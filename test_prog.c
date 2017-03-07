#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  int year = 0;
  if (argc < 2){
    fprintf(stderr, "%s [year]\n\n", argv[0]);
    return -1;
  }
  year = atoi(argv[1]);
  if (s_isleap(year))
    printf("%d is a leap year\n", year);
  else
    printf("%d is not a leap year\n", year);

  return 0;
}
