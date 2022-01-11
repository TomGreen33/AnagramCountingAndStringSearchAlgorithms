/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "header.h"


/* Algorithm that returns the list of anagrams of an input string within a word list by utilizing the presorting technique
 * @param wordList: Word list to be searched in
 * @param inputString: Input string from which anagrams must be found
 * @return the number of anagrams
 */
wordList getAnagramsBinary(wordList wordList, char *inputString) {

  /* This algorithm uses a lot of the same logic as that of binary search */
  int left;
  int right;
  int mid;

  long inputSignature;          /* Signature of the input string */
  long signature;               /* Signature of a given word */
  int base;                     /* The index of the first word who's signature matches that of the input signature */
  int traverse;                 /* Used to find neighboring anagrams around base */
  struct wordList anagramList;  /* The anagrams list */
  int numAnagrams;

  numAnagrams = 0;
  anagramList.words = (char**)malloc(0);
  inputSignature = getSignature(inputString);

  left = 0;
  right = wordList.numWords - 1;

  /* While the subarray of interest is greate than size zero */
  while (left <= right)
  {
    /* Find the signature of the middle element of the current subarray */
    mid = floor((left + right) / 2);
    signature = getSignature(wordList.words[mid]);

    /* If the signature of this element is the same as that of the input signature */
    if (signature == inputSignature)
    {
      /* Set base to this newly found element */
      base = mid;

      /* If this newly found element is distinct from the input string, add this element to anagrams list */
      if (strcmp(inputString, wordList.words[base]) != 0)
      {
        numAnagrams += 1;
        anagramList.words = (char**)realloc(anagramList.words, numAnagrams * sizeof(char*));
        anagramList.words[numAnagrams-1] = wordList.words[base];
      }

      /* Check for anagrams on the left of this element */
      traverse = base - 1;
      while (getSignature(wordList.words[traverse]) == signature)
      {
        if (strcmp(inputString, wordList.words[traverse]) != 0)
        {
          numAnagrams += 1;
          anagramList.words = (char**)realloc(anagramList.words, numAnagrams * sizeof(char*));
          anagramList.words[numAnagrams-1] = wordList.words[traverse];
        }
        traverse --;
      }

      /* Check for anagrams on the right of this element */
      traverse = base + 1;
      while (getSignature(wordList.words[traverse]) == signature)
      {
        if (strcmp(inputString, wordList.words[traverse]) != 0)
        {
          numAnagrams += 1;
          anagramList.words = (char**)realloc(anagramList.words, numAnagrams * sizeof(char*));
          anagramList.words[numAnagrams-1] = wordList.words[traverse];
        }
        traverse ++;
      }

      /* Return the anagrams list */
      anagramList.numWords = numAnagrams;
      return anagramList;
    }

    /* If no anagram was found at mid, make the subarray smaller accordingly */
    else if (inputSignature < signature)
    {
      right = mid - 1;
    }
    else
    {
      left = mid + 1;
    }
  }

  anagramList.numWords = numAnagrams;
  return anagramList;
}
