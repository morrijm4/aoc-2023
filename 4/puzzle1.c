#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int getPoints(char *line) {
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

  int points = 0;
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
        if (points) {
          points *= 2;
        } else {
          points = 1;
        }
      }
    }
    line++;
  }

  return points;
}

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  int ans = 0;
  char line[256];
  while (fgets(line, sizeof(line), fp) != NULL) {
    ans += getPoints(line);
  }

  printf("Answer: %d\n", ans);

  fclose(fp);
}
