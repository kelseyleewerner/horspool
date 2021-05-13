#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Find the location of the first occurrence of pattern in text
// or say that it does not occur if that is the case.
// If you find the pattern in the text, output the index of the
// first letter in text where the pattern first occurs.

// You must also print the total number of character compairsons that
// the program made.

// If the number of unchecked characters in the text is ever less than
// the length of the pattern the algorithm must stop.

// NOTE:  All test texts and patterns should not contain any white space
//        (e.g. blank space character, newline, tab, etc.) as scanf
//        will stop on such an input character.


#define TABLE_SIZE 128

int ASCII_TABLE[TABLE_SIZE];
int COUNT = 0;

int horspool_wrapper(char *, int, char *, int);
int horspool(char *, int, char *, int, int);


int main()
{
  char text[10000] ;
  char pattern[200] ;
  int m,n,result ;

  printf("enter text : ") ;
  scanf("%s", text) ;
  printf("enter pattern you are searching for : ") ;
  scanf("%s", pattern) ;

  m = strlen(pattern) ;
  n = strlen(text) ;
  printf("The pattern has %d characters and the text has %d characters.\n", m,n) ;

  result = horspool_wrapper(pattern, m, text, n);

  if (result == -1)
    printf("The pattern is not contained in this text.\n");
  else
    printf("The first instance of the pattern found in the text begins at index %d.\n", result);

  printf("The number of character comparisons was %d.\n", COUNT);
}


int horspool_wrapper(char * pattern, int pattern_length, char * text, int text_length)
{
  int pl = pattern_length - 1;

  for (int i = 0; i < TABLE_SIZE; ++i) { ASCII_TABLE[i] = pattern_length; }

  ASCII_TABLE[pattern[pl]] = pattern_length;

  for (int i = 0; i < pattern_length - 1; ++i) { ASCII_TABLE[pattern[i]] = pl--; }

  return horspool(pattern, pattern_length, text, text_length, pattern_length - 1);
}


int horspool(char * pattern, int pattern_length, char * text, int text_length, int start)
{
  int found = -1;
  int i, j;

  if (start > text_length - 1) { return -1;}

  for (j = pattern_length - 1, i = start; j >= 0; --j, --i) {
    ++COUNT;

    if (pattern[j] != text[i]) { break; }

    if (j == 0) { return i; }
  }

  return horspool(pattern, pattern_length, text, text_length, start + ASCII_TABLE[text[start]]);
}

