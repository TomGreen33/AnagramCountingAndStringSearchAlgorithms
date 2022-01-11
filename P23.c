/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <stdbool.h>
 #include <ctype.h>
 #include <string.h>
 #include "header.h"


 /* Boyer Moore algorithm that computes the number of occurences of a pattern within a text
  * @param text: The text to be searched in
  * @param pattern: The pattern to be searched for
  * @return the number of occurences of a pattern within a text, as well as the number of shifts utilized by the algorithm
  */
struct stringSearch stringMatchBoyerMoore (struct text text, struct text pattern) {

  long *badSymbolShiftTable;
  long *goodSuffixTable;
  int i;
  int k;
  long d;
  long d1;
  long d2;
  struct stringSearch stringSearch;

  badSymbolShiftTable = getShiftTable(pattern);
  goodSuffixTable = getGoodSuffixTable(pattern);

  stringSearch.numShifts = 0;
  stringSearch.numOccurences = 0;

  i = pattern.length - 1;

  /* While the text pointer is within bounds */
  while (i < text.length)
  {
    k = 0;

    /* Count the number of matching characters (between the text and pattern) from left to right */
    while (k <= pattern.length - 1 && pattern.ptr[pattern.length - 1 - k] == text.ptr[i-k])
    {
      k++;
    }

    /* If k >= 0, retrieve d1. i.e. do this every time */
    if (badSymbolShiftTable[map(text.ptr[i-k])] - k > 1)
    {
      d1 = badSymbolShiftTable[map(text.ptr[i-k])] - k;
    }
    /* d1 has to be a positive interger */
    else
    {
      d1 = 1;
    }

    /* If k > 0, retrieve d2 */
    if (k > 0)
    {
      d2 = goodSuffixTable[k-1];
    }

    /* d = d1 if k = 0 */
    if (k == 0)
    {
      d = d1;
    }

    /* d = max(d1, d2) if k > 0 */
    else
    {
      if (d1 > d2)
      {
        d = d1;
      }
      else
      {
        d = d2;
      }
    }

    /* If there is a match */
    if (k == pattern.length)
    {
      /* Increment occurences, shifts, text pointer */
      stringSearch.numOccurences++;
      stringSearch.numShifts++;
      i += d;
    }
    else
    {
      /* Increment shifts, text pointer */
      stringSearch.numShifts++;
      i += d;
    }
  }

  return stringSearch;
}


/* Computes the good suffix table of a given pattern
 * @param pattern: The pattern from the which table will be created
 * @return the good suffix table
 */
 long *getGoodSuffixTable(struct text pattern) {

   long k;
   long *goodSuffixTable;

   /* Define array of size m - 1 */
   goodSuffixTable = (long*)malloc((pattern.length - 1) * sizeof(long));

   /* For each index of the array, find the corresponding D2 value */
   for (k = 1; k < pattern.length; k++)
   {
     goodSuffixTable[k-1] = getD2(pattern, k);
   }

   return goodSuffixTable;
 }


 /* Computes d2 for a given pattern and value k
  * @param k: The size of the suffix
  * @return d2
  */
long getD2(struct text pattern, long k) {

  long m;
  long d2;
  long l;
  long lMax;
  long i;
  struct text suffix;
  struct text prefix;
  struct text patternSection;

  m = pattern.length;
  d2 = 0;
  lMax = 0;

  /* Allocate space of pattern section of size k */
  patternSection.ptr = (char*)malloc(k * sizeof(char));

  /* Define suffix of size k */
  suffix.ptr = (char*)malloc(k * sizeof(char));
  suffix.length = k;
  strncpy(suffix.ptr, &pattern.ptr[pattern.length - k], k);
  suffix.ptr[k] = '\0';

  /* Move pattern section from right of the pattern to the left */
  for (i = m - k - 1; i >= 0; i--)
  {
    d2++;
    strncpy(patternSection.ptr, &pattern.ptr[i], k);
    patternSection.ptr[k] = '\0';

    /* If the pattern section and suffix are the same, return the distance between them */
    if (strcmp(patternSection.ptr, suffix.ptr) == 0)
    {
      return d2;
    }
  }

  prefix.ptr = (char*)malloc(0);

  /* For every suffix and prefix of size l betweem 1 and k - 1 */
  for (l = 1; l < k; l++)
  {
    /* Define the suffic and prefix of size l */
    prefix.ptr = (char*)realloc(prefix.ptr, l * sizeof(char));
    suffix.ptr = (char*)realloc(suffix.ptr, l * sizeof(char));

    strncpy(prefix.ptr, pattern.ptr, l);
    strncpy(suffix.ptr, &pattern.ptr[m - l], l);

    prefix.ptr[l] = '\0';
    suffix.ptr[l] = '\0';

    /* If the suffix and prefix of size l are found to be the same */
    if (strcmp(prefix.ptr, suffix.ptr) == 0)
    {
      lMax = l;
    }
  }

  /* If there exists no suffix/prefix that match, d2 = m */
  if (lMax == 0)
  {
    d2 = m;
  }
  else
  {
    d2 = m - lMax;
  }

  return d2;
 }
