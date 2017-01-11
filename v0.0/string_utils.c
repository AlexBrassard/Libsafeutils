#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include "string_op.h" /* Main string operation header file. */


/* Copy source into destination of size n (including the trailing NUL byte).
   Note, SU_strcpy() always clears the buffer before
   copying results into it. */
void *SU_strcpy(char *dest, char *src, size_t n)
{
  size_t src_s = 0;
  size_t dest_s = 0;
  /* Added for debug when using with the libfindf.so library 
  fprintf(stderr, "Begining SU_strcpy()\ndest: %s\nsrc: %s\nsize 'n': %lu\n", 
	  dest[0] != '\0' ? dest : "NULL", src != NULL ? src : "NULL", n);
  */


  if (dest != NULL                /* We need an already initialized buffer. */
      && src != NULL              /* We need a valid, non-empty source. */
      && src[0] != '\0'
      && n > 0                    /* Destination buffer's size must be bigger than 0, */ 
      && n < (SIZE_MAX - 1))      /* and smaller than it's type size - 1. */
    /* Note that both last test above simply cannot fail, size_t being 
       unsigned int wrap-arround will occur and produce wierd values, worse
       may somehow be vulnerable to an attack. */
    ; /* Valid input. */
  else {
    errno = EINVAL;
    return NULL;
  }
  
  /* Look out for a NUL byte, never past SIZE_MAX - 1. */
  src_s = strnlen(src, SIZE_MAX - 1);
  if (src_s > n - 1){ /* -1, we always add a NUL byte at the end of string. */
    errno = EOVERFLOW;
    fprintf(stderr,"%s: %d: Source must be at most destination[n - 1]\n\n", __func__, __LINE__);
    dest = NULL;
    return dest;
  }

  memset(dest, 0, n);
  memcpy(dest, src, src_s);
  /* Add a trailing NUL byte. */
  dest_s = strlen(dest);
  if (dest[dest_s] != '\0')
    dest[dest_s] = '\0';
  

  /* Adding for debug with the libfindf.so library. 
     fprintf(stderr, "\ndest: %s\n\n",dest);*/


  return dest;
}

