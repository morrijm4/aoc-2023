#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define GAMES 219

int getCountOfWinningNumbers(char *line) {
  int map[100] = {0}; // numbers range is 0 < x < 100

  // interate past game id
  while (*line++ != ':') {
  }

  while (*line != '|') {
    if (isdigit(*line)) {
      int i = 0;
      char num[3];

      while (isdigit(*line)) {
        num[i++] = *line++;
      }
      num[i] = '\0';

      int val = atoi(num);
      map[val] = val;
    }
    line++;
  }

  int count = 0;
  while (*line != '\0') {
    if (isdigit(*line)) {
      int i = 0;
      char num[3];

      while (isdigit(*line)) {
        num[i++] = *line++;
      }
      num[i] = '\0';

      int val = atoi(num);
      if (map[val] == val) {
        count++;
      }
    }
    line++;
  }

  return count;
}

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  int game = 0;
  int ans = 0;
  char line[256];
  int scratchcard_copies[GAMES];

  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }
  
  for (int i = 0; i < GAMES; i++) {
    scratchcard_copies[i] = 1;
  }

  while (fgets(line, sizeof(line), fp) != NULL) {
    int count = getCountOfWinningNumbers(line);
    for (int i = 1; i <= count && (game + i) < GAMES; i++) {
      scratchcard_copies[i + game] += scratchcard_copies[game];
    }
    game++;
  }

  for (int i = 0; i < GAMES; i++) {
    ans += scratchcard_copies[i];
  }

  printf("Answer: %d\n", ans);

  fclose(fp);
}
