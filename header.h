typedef struct wordList {
  char **words;
  char **signatures;
  int numWords;
} wordList;


typedef struct text {
  char *ptr;
  long length;
} text;


typedef struct stringSearch {
  long numShifts;
  long numOccurences;
} stringSearch;


/* Main */
int getNumLength(int number);
void sortBySignature(wordList wordList);
long getSignature(char *word);

/* P1.1 */
wordList getAnagramsBruteForce(wordList wordList, char *inputString);
bool isAnagram(char *string1, char *string2);

/* P1.2 */
wordList getAnagramsBinary(wordList wordList, char *inputString);

/* P2.1 */
struct stringSearch stringMatchBruteForce(struct text text, struct text pattern);

/* P2.2 */
struct stringSearch stringMatchHorspool (struct text text, struct text pattern);
long *getShiftTable(struct text pattern);
int map(char character);

/* P2.3 */
struct stringSearch stringMatchBoyerMoore (struct text text, struct text pattern);
long *getGoodSuffixTable(struct text pattern);
long getD2(struct text pattern, long k);
