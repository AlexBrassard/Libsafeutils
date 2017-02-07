#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  int ret = 0, i = 0;
  int delim = 0;
  char **dest = NULL;
  

  if (argc < 3) {
    fprintf(stderr, "s_split() : split the given string according to the given delimiter.\n\n");
    return -1;
  }

  if ((dest = malloc(256 * sizeof(char*))) == NULL){
    perror("Malloc");
    return -1;
  }
  for (; i < 256; i++)
    if ((dest[i] = calloc(256, sizeof(char))) == NULL){
      perror("Calloc");
      return -1;
    }
  delim = argv[2][0];
  if (s_split(dest, argv[1], 256, strlen(argv[1])+1, 256, delim) == NULL){
    perror("S_split");
    return -1;
  }
  printf("Dest is:\n");
  for (i = 0; i < 256 && dest[i][0] != '\0'; i++)
    printf("[%d] - %s\n", i, dest[i]);
  
  return 0;
}
