/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include "header.h"


/* Horspool algorithm that computes the number of occurences of a pattern within a text
 * @param text: The text to be searched in
 * @param pattern: The pattern to be searched for
 * @return the number of occurences of a pattern within a text, as well as the number of shifts utilized by the algorithm
 */
struct stringSearch stringMatchHorspool (struct text text, struct text pattern) {

  long *shiftTable;
  int i;
  int j;
  struct stringSearch stringSearch;

  stringSearch.numShifts = 0;
  stringSearch.numOccurences = 0;

  /* Create shift table for a given pattern */
  shiftTable = getShiftTable(pattern);

  i = pattern.length - 1;

  /* While the text pointer is within bounds */
  while (i < text.length)
  {
    j = 0;

    /* Count the number of matching characters (between the text and pattern) from left to right */
    while (j <= pattern.length - 1 && pattern.ptr[pattern.length - 1 - j] == text.ptr[i-j])
    {
      j++;
    }

    /* If there is a match */
    if (j == pattern.length)
    {
      /* Increment occurences, shifts, text pointer */
      stringSearch.numOccurences++;
      stringSearch.numShifts++;
      i += shiftTable[map(text.ptr[i])];
    }
    else
    {
      /* Increment shifts, text pointer */
      stringSearch.numShifts++;
      i += shiftTable[map(text.ptr[i])];
    }
  }

  return stringSearch;
}


/* Computes the shift table of a given pattern
 * @param pattern: The pattern from the which table will be created
 * @return the shift table
 */
long *getShiftTable(struct text pattern) {

  int i;
  long *shiftTable;

  shiftTable = (long*)malloc(53 * sizeof(long));

  /* Initialize each shift table element to be the pattern length */
  for (i = 0; i < 53; i++)
  {
    shiftTable[i] = pattern.length;
  }
  /* For each character of the pattern */
  for (i = 0; i < pattern.length - 1; i++)
  {
    /* Overwrite the corresponding shift table element to be
    the distance between the character and the end of the pattern */
    shiftTable[map(pattern.ptr[i])] = pattern.length - 1 - i;
  }

  return shiftTable;
}


/* Maps a character (upper or lowercase letter/other) to an index of the shift table
 * @param character: The character to be mapped
 * @return the shift table index
 */
int map(char character) {

  int index;

  /* Index 0:25 -> lower case characters */
  if (islower(character) != 0)
  {
    index = character - 'a';
  }
  /* Index 26:50 -> upper case characters */
  else if (isupper(character) != 0)
  {
    index = character - 'A' + 26;
  }
  /* Index 52 -> other */
  else
  {
    index = 52;
  }

  return index;
}
