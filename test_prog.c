#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "sutils.h"

int main(int argc, char **argv)
{
  char string[256];
  char **words = NULL;
  size_t i = 0;

  if (argc <= 1) {
    fprintf(stderr, "%s [string] at most 255 bytes\n\n", argv[0]);
    return -1;
  }
  if ((words = malloc(256 * sizeof(char*))) == NULL){
    perror("Malloc");
    return -1;
  }
  while(i < 256){
    if ((words[i] = calloc(256, sizeof(char))) == NULL){
      perror("Calloc");
      return -1;
    }
    ++i;
  }
  if (s_strcpy(string, argv[1], 256) == NULL){
    perror("S_strcpy");
    return -1;
  }

  if (s_split(words, (const char*)string,
	      256, 256, -1) == NULL){
    perror("S_split");
    return -1;
  }
  for (i = 0; i < 256; i++)
    if (words[i][0] != '\0')
      printf("Word[%3zu]: %s\n", i, words[i]);
    else break;
  
  return 0;
}
