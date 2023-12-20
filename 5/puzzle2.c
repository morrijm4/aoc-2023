#include "utils2.c"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>

#define PAIRS 2

// Requires a new line at the end of the file.

int main(void) {

  FILE *file_pointer = fopen("input.txt", "r");
  if (file_pointer == NULL) {
    perror("unable to open file");
    return 1;
  }

  char buf[256];
  if (fgets(buf, sizeof(buf), file_pointer) == NULL) {
    printf("unable to read first line");
    return 1;
  }

  SeedPair pairs[PAIRS] = {0};
  getSeedPairs(buf, sizeof(buf), pairs, PAIRS);

  calculateSeeds(pairs, PAIRS);

  while (fgets(buf, sizeof(buf), file_pointer) != NULL) {
    // handle map if line starts with a digit
    if (isdigit(buf[0])) { 
      interpretMap(parseMap(buf));
    }

    if (buf[0] == '\n') {
      commitSeeds();
    }
  }

  printLowest();
  return 0;
}
