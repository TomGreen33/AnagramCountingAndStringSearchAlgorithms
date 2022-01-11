/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"


/* Brute force algorithm that computes the number of occurences of a pattern within a text
 * @param text: The text to be searched in
 * @param pattern: The pattern to be searched for
 * @return the number of occurences of a pattern within a text, as well as the number of shifts utilized by the algorithm
 */
struct stringSearch stringMatchBruteForce (struct text text, struct text pattern) {

  long i;
  struct text textSection;
  struct stringSearch stringSearch;
  stringSearch.numOccurences = 0;
  stringSearch.numShifts = 0;

  textSection.ptr = (char*)malloc(pattern.length * sizeof(char));
  textSection.length = pattern.length;

  for (i = 0; i < text.length; i++)
  {
    strncpy(textSection.ptr, &text.ptr[i], pattern.length);
    textSection.ptr[textSection.length] = '\0';
    if (strcmp(textSection.ptr, pattern.ptr) == 0)
    {
      stringSearch.numOccurences++;
    }
    stringSearch.numShifts++;
  }

  return stringSearch;
}
