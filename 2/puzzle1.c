#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 512

#define RED_CUBES 12
#define GREEN_CUBES 13
#define BLUE_CUBES 14

int getMaxCubesForColor(char color) {
  switch (color) {
    case 'r':
      return RED_CUBES;
    case 'g':
      return GREEN_CUBES;
    case 'b':
      return BLUE_CUBES;
    default:
      printf("Unexpected color %c\n", color);
      exit(1);
  }
}

int isGamePossible(char *buf) {
  // loop past game id
  while (*buf++ != ':') {}

  char cubes[3];
  while (*buf++ != '\0') {
    if (isdigit(*buf)) {
      // build number of cubes string
      int i = 0;
      while (isdigit(*buf)) {
	cubes[i++] = *buf++;
      }
      cubes[i] = '\0';

      int num_cubes = atoi(cubes);
      if (num_cubes > getMaxCubesForColor(*++buf)) {
	return 0; // impossible
      }
    }

  }
  return 1; // possible
}

int getGameId(char *buf) {
  char str[64];

  // Go to first digit in game id
  buf += 5;
  
  int i = 0;
  while (buf[i] != ':') {
    str[i] = buf[i];
    i++;
  }
  str[i] = '\0';

  return atoi(str);
}

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }
  
  char buf[BUF_SIZE];
  int total;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    if (isGamePossible(buf)) {
      total += getGameId(buf);
    }
  }

  printf("Answer: %d\n", total);

  fclose(fp);
  return 0;
}
