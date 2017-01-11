/*
 *
 * Safe-utils Library  -  Header and code file.
 * Version 1.0
 *
 */

#ifndef LIB_SAFE_UTILS_HEADER_FILE
# define LIB_SAFE_UTILS_HEADER_FILE

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>

/*** Code ***/

/*
 * Copy at most dest_s-1 char from src to dest,
 * filling the buffer with zeros before copying the data.
 */
static inline char* s_strcpy(char *dest, char *src, size_t dest_s)
{
  size_t src_s = 0;
  
  if (!dest || !src || !dest_s){
    errno = EINVAL;
    return NULL;
  }

  if ((src_s = strlen(src)) > dest_s-1){
    errno = EOVERFLOW;
    fprintf(stderr, "%s: Source must be at most destination[n-1]\n\n", __func__);
    return NULL;
  }
  memset(dest, '\0', dest_s);
  memcpy(dest, src, src_s);
  return dest;

} /* s_strcpy() */


/* Convert the double integer src into a dest_s-1 precision string dest. */
static inline char* s_ftoa(char *dest, double src, size_t dest_s)
{
  if (!dest || dest_s < 2) {
    errno = EINVAL;
    return NULL;
  }
  memset(dest, '\0', dest_s);
  if (snprintf(dest, dest_s-1, "%f", src) < 0) {
    fprintf(stderr, "%s: Failed to print the given number to the given buffer\n\n", __func__);
    return NULL;
  }
  dest[strlen(dest)] = '\0';

  return dest;

} /* s_ftoa() */


/* Converts the integer src into a dest_s-1 digits string dest. */
static inline char* s_itoa(char *dest, int src, size_t dest_s)
{
  if (!dest || dest_s < 2) {
    errno = EINVAL;
    return NULL;
  }
  memset(dest, '\0', dest_s);
  if (snprintf(dest, dest_s-1, "%d", src) < 0) {
    fprintf(stderr, "%s: Failed to print the given number to the given buffer\n\n", __func__);
    return NULL;
  }
  dest[strlen(dest)] = '\0';

  return dest;

} /* s_itoa() */

/* 
 * Split src into dest[words] of at most word_s-1 characters each,
 * words are all null terminated and
 * separated by the word_delim character casted to an integer (space by default).
 * Set word_delim to -1 for default.
 * dest can hold at most dest_s-1 words.
 */
static inline char** s_split(char **dest, const char* src, size_t dest_s,
			     size_t word_s, int word_delim)
{
  size_t src_ind = 0, dest_ind = 0, word_ind = 0;
  int delimiter = ' ';                             /* Space delimited words unless told otherwise. */

  if (!dest || !src || src[0] == '\0'
      || !dest_s || !word_s){
    errno = EINVAL;
    return NULL;
  }
  if (word_delim >= 0) delimiter = word_delim;
  
  while(dest_ind < dest_s){
    /* 
     * Return successfuly if there's at least 1 word in the 
     * destination array and the next word is NULL. 
     */
    if (!dest[dest_ind]){
      if (dest_ind > 0)
	break;
      else{
	errno = ENODATA;
	fprintf(stderr, "%s: dest must contain at least one initialized char array.\n\n", __func__);
	return NULL;
      }
    }
    /* Clear the current word buffer. */
    memset(dest[dest_ind], '\0', word_s);

    /* Get a word. */
    while(1){
      if (src[src_ind] == '\0') {
	dest[dest_ind][word_ind] = '\0';
	return dest;
      }
      /* Finding a word that doesn't fit in a word buffer is an error. */
      if (word_ind >= word_s){
	errno = EOVERFLOW;
	fprintf(stderr, "%s: The word following \"%s\" does not fit in the given buffer size '%zu'\n\n",
		__func__, ((dest_ind > 0) ? dest[dest_ind-1] : "NO WORD REGISTERED"), word_s);
	return NULL;
      }
      /* Null terminate the current word when hitting the delimiter. */
      if (src[src_ind] == delimiter) {
	dest[dest_ind][word_ind] = '\0';
	word_ind = 0;
	++dest_ind;
	++src_ind;
	break;
      }
      /* Add the current src character to the current dest word. */
      dest[dest_ind][word_ind] = src[src_ind];
      ++word_ind;
      ++src_ind;
    }
  }

  return dest;
}
	       

#endif /* LIB_SAFE_UTILS_HEADER_FILE */
