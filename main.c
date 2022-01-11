/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 3
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "header.h"


int main (int argc, char *argv[]) {

  FILE *fp;
  int selection;
  int i;
  int j;
  double executionTime;
  time_t begin;
  time_t end;
  long line[5];
  char inputString[100];
  struct wordList wordList;
  struct wordList anagramList;
  struct text text;
  struct text pattern;
  struct stringSearch stringSearch;


  printf("*================================================================*\n");
  printf("|   Option 1: Find anagrams using brute force algorithm          |\n");
  printf("|   Option 2: Find anagrams using smart algorithm                |\n");
  printf("|   Option 3: Search for string using brute force algorithm      |\n");
  printf("|   Option 4: Search for string using Horspool's algorithm       |\n");
  printf("|   Option 5: Search for string using Boyer-Moore's algorithm    |\n");
  printf("*================================================================*\n\n");

  printf("Please make a selection: ");
  scanf("%d", &selection);

  if (selection < 1 || selection > 5)
  {
    printf("Invalid selection\n");
    return 0;
  }

  /* If Option 1 or option 2, read in anagrams.txt into memory */
  if (selection == 1 || selection == 2)
  {
    wordList.words = (char**)malloc(sizeof(char*));

    i = 0;
    fp = fopen("anagrams.txt", "rb");

    while (!feof (fp))
    {
      wordList.words = (char**)realloc(wordList.words, (i+5) * sizeof(char*));
      fscanf(fp, "%ld %ld %ld %ld %ld\n", &line[0], &line[1], &line[2], &line[3], &line[4]);

      /* Allocate space for each word  and assign it it's value */
      for (j = 0; j < 5; j++)
      {
        wordList.words[i+j] = (char*) malloc(getNumLength(line[j]) * sizeof(char));
        sprintf(wordList.words[i+j], "%ld", line[j]);
      }
      i += 5;
    }

    fclose(fp);
    wordList.numWords = i;

    printf("Input String: ");
    scanf("%s", inputString);
  }

  /* Excecute brute force anagrams algorithm */
  if (selection == 1)
  {
    begin = clock();

    anagramList = getAnagramsBruteForce(wordList, inputString);

    end = clock();
    executionTime = (double)(end - begin);
  }
  /* Excecute efficient anagrams algorithm */
  else if (selection == 2)
  {
    sortBySignature(wordList);

    begin = clock();
    anagramList = getAnagramsBinary(wordList, inputString);
    end = clock();
  }

  /* Show output for anagrams counting algorithm */
  if (selection == 1 || selection == 2)
  {
    printf("\nThe following are all the anagrams of input %s:\n\n", inputString);

    for (i = 0; i < anagramList.numWords; i++)
    {
      printf("Anagram %d: %s\n", i+1, anagramList.words[i]);
    }

    printf("\nNumber of anagrams: %d\n\n", anagramList.numWords);
    printf("Execution time for the algorithm: %.20f seconds\n", (double)executionTime/CLOCKS_PER_SEC);
  }


  /* If option 3, option 4, or option 5, read in stringSearch.txt into memory */
  else if (selection == 3 || selection == 4 || selection == 5)
  {
    fp = fopen("stringSearch.txt", "rb");
    fseek(fp, 0, SEEK_END);
    text.length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    text.ptr = (char*)malloc(text.length * sizeof(char));
    fread(text.ptr, sizeof(char), text.length, fp);
    fclose(fp);

    printf("\nInput String: ");
    scanf("%s", inputString);
    pattern.length = strlen(inputString);
    pattern.ptr = (char*)malloc(pattern.length * sizeof(char));
    strcpy(pattern.ptr, inputString);
  }

  /* Excecute brute force string search algorithm */
  if (selection == 3)
  {
    begin = clock();

    stringSearch = stringMatchBruteForce(text, pattern);

    end = clock();
    executionTime = (double)(end - begin);
  }
  /* Excecute Horspool string search algorithm */
  if (selection == 4)
  {
    begin = clock();

    stringSearch = stringMatchHorspool(text, pattern);

    end = clock();
    executionTime = (double)(end - begin);
  }

  /* Excecute Boyer Moore string search algorithm */
  if (selection == 5)
  {
    begin = clock();

    stringSearch = stringMatchBoyerMoore(text, pattern);

    end = clock();
    executionTime = (double)(end - begin);
  }

  /* Show output for string search algorithm */
  if (selection == 3 || selection == 4 || selection == 5)
  {
    printf("\nNumber of occurences for input %s: %ld\n\nNumber of shifts excecuted by the algorithm: %ld\n\n", inputString, stringSearch.numOccurences, stringSearch.numShifts);
    printf("Execution time for the algorithm: %f seconds\n", (double)executionTime/CLOCKS_PER_SEC);
  }

  return 0;
}

/* computes the number of digits in a given number (e.g. 59385 -> 5)
 * @param number: The number to be assessed
 * @return the number of digits in the number
 */
int getNumLength(int number) {

  return floor(log10(abs(number))) + 1;
}


/* Sorts a given word list by signature
 * @param wordList: The word list to be sorted
 */
void sortBySignature(wordList wordList) {

  int i;
  int j;
  int min;
  long *signatures;
  long signature;
  long minSignature;
  char *temp;

  /* Create a list containing signatures derived from the original word list */
  signatures = (long*)malloc(wordList.numWords * sizeof(long));
  for (i = 0; i < wordList.numWords; i++)
  {
    signatures[i] = getSignature(wordList.words[i]);
  }

  temp = (char*)malloc(sizeof(char));

  /* Using selection sort, sort the wordlist by also sorting the signatures list */
  for (i = 0; i < wordList.numWords -1; i++)
  {
    minSignature = signatures[i];
    min = i;

    for (j = i + 1; j < wordList.numWords; j++)
    {
      signature = signatures[j];
      if (signature < minSignature)
      {
        minSignature = signature;
        min = j;
      }
    }
    temp = realloc(temp, strlen(wordList.words[min]) * sizeof(char));
    strcpy(temp, wordList.words[min]);
    strcpy(wordList.words[min], wordList.words[i]);
    strcpy(wordList.words[i], temp);
    signature = signatures[min];
    signatures[min] = signatures[i];
    signatures[i] = signature;
  }
}

/* Computes the signature of a given word
 * @param word: The word from which the signauture will be computed
 * @return the signature
 */
long getSignature(char *word) {

  int i;
  int j;
  int numberFreq[10];
  long signature;

  signature = 0;

  /* Initialize number frequencies to be zero */
  for (i = 0; i < 10; i++)
  {
    numberFreq[i] = 0;
  }

  /* For each character in the string, increment the corresponding index in numberFreq
   * where the index of the array matches the charater or interest
   */
  for (i = 0; i < strlen(word); i++)
  {
    numberFreq[word[i] - '0']++;
  }

  /* For each number (in decending order) */
  for (i = 9; i >= 0; i--)
  {
    /* Muliply signauture by 10 and add a given number */
    /* Do this however many times the number appeared in the original word */
    for (j = 0; j < numberFreq[i]; j++)
    {
      signature *= 10;
      signature += i;
    }
  }

  return signature;
}
