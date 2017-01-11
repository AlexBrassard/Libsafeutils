#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "string_op.h"

int main(int argc, char **argv)
{
  char dest[255];
  int i;

  if (argc < 2) abort();
  
  if (SU_memcpy(dest, argv[1], 255) != NULL){
      printf("dest is: %s\n", dest);
      for (i = 0; dest[i] != '\0'; i++)
	printf("dest[%d]: %c\n", i, dest[i]);
  }
  return 0;
}
