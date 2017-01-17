#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  char **dest = NULL;
  int i = 0;
  


  if (argc < 2){
    fprintf(stderr, "%s [string]  -  Split a string into at most 255 words of at most 255 characters each, 1 per line.\n\n",
	    argv[0]);
    return -1;
  }

  if ((dest = malloc(256 * sizeof(char*))) == NULL){
    perror("Malloc");
    return -1;
  }
  while (i < 256)
    if ((dest[i++] = calloc(256, sizeof(char))) == NULL){
      perror("Calloc");
      return -1;
    }
  
  if (s_split(dest, (const char*)argv[1], 256,
	      strlen(argv[1]), 256, ':') == NULL){
    perror("S_split");
    return -1;
  }
  for (i = 0; dest[i][0] != '\0' && i < 256; i++)
    printf("%s\n", dest[i]);
    
  
  return 0;
}
