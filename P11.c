/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"


/* Brute force algorithm that computes the number of anagrams of input string within a word list
 * @param wordList: Word list to be searched in
 * @param inputString: Input string from which anagrams must be found
 * @return the number of anagrams
 */
wordList getAnagramsBruteForce(wordList wordList, char *inputString) {

  int i;
  bool isNewAnagram;
  int numAnagrams;
  struct wordList anagramList;

  numAnagrams = 0;

  /* For each word in the word list */
  for (i = 0; i < wordList.numWords; i++)
  {

    isNewAnagram = false;

    /* If a given word is different from the input string */
    if (strcmp(inputString, wordList.words[i]) != 0)
    {
      /* Check if the word and the input string are anagrams of each other */
      isNewAnagram = isAnagram(inputString, wordList.words[i]);
    }

    /* If a word is found to be an anagram of the input string */
    if (isNewAnagram == true)
    {
      /* Increment anagrams */
      numAnagrams++;

      /* Allocate space for the new anagram */
      if (numAnagrams == 1)
      {
        anagramList.words = (char**)malloc(sizeof(char*));
      }
      else
      {
        anagramList.words = (char**)realloc(anagramList.words, numAnagrams * sizeof(char*));
      }

      /* Copy the newly found anagram into the anagram list */
      anagramList.words[numAnagrams-1] = wordList.words[i];
    }
  }

  anagramList.numWords = numAnagrams;

  return anagramList;
}


/* Determines if 2 strings are anagrams of each other
 * @param string1: String 1
 * @param string2: String 2
 * @return whether the 2 strings are anagrams of each other
 */
bool isAnagram(char *string1, char *string2) {

  /* Since data_4.txt is composed of numbers, we only need to check for the frequency of numbers 0-9, hence the array size of 10 */
  
  int numberFreq1[10]; /* Frequency of each number in string 1 */
  int numberFreq2[10]; /* Frequency of each number in string 2 */
  int i;

  /* Initialize frequencies to zero */
  for (i = 0; i < 10; i++)
  {
    numberFreq1[i] = 0;
    numberFreq2[i] = 0;
  }

  /* For each character of string 1, increment the corresponding element in numberFreq1 */
  for (i = 0; i < strlen(string1); i++)
  {
    numberFreq1[string1[i] - '0']++;
  }

  /* For each character of string 2, increment the corresponding element in numberFreq2 */
  for (i = 0; i < strlen(string2); i++)
  {
    numberFreq2[string2[i] - '0']++;
  }

  /* Compare the frequency of each number between the 2 strings */
  for (i = 0; i < 10; i++)
  {
    /* If the frequencies of a given number differs between the 2 strings, return false */
    if (numberFreq1[i] != numberFreq2[i])
    {
      return false;
    }
  }

  return true;
}
