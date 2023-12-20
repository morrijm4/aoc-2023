#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define RACES 4
#define RATE 1

typedef struct Race {
  int time;
  int distance;
} Race;

void printRaces(Race *races) {
  for (size_t i = 0; i < RACES; ++i) {
    printf("Time: %d\n", races[i].time);
    printf("Distance: %d\n", races[i].distance);
    printf("\n");
  }
}

/**
 * Parse input.txt file and create an array of Race structs. Write to passed
 * Race pointer.
 *
 * @param races - Race array size RACES.
 * @return - int status code.
 */
int getRaces(Race *races) {
  FILE *file_pointer = fopen("input.txt", "r");
  if (file_pointer == NULL) {
    perror("unable to open file");
    return 1;
  }

  char lineBuf[64];

  // Load the times

  if (fgets(lineBuf, sizeof(lineBuf), file_pointer) == NULL) {
    printf("error reading first line\n");
    return 1;
  }

  size_t raceCount = 0;
  size_t i = 0;
  while (lineBuf[i] != '\n' && i < sizeof(lineBuf) && raceCount < RACES) {
    if (!isdigit(lineBuf[i])) {
      i++;
      continue;
    }

    char numberBuf[16];
    size_t j = 0;
    while (isdigit(lineBuf[i])) {
      numberBuf[j++] = lineBuf[i++];
    }
    numberBuf[j] = '\0';

    races[raceCount++].time = atoi(numberBuf);
  }

  // Load the distances

  if (fgets(lineBuf, sizeof(lineBuf), file_pointer) == NULL) {
    printf("error reading first line\n");
    return 1;
  }

  raceCount = 0;
  i = 0;
  while (lineBuf[i] != '\n' && i < sizeof(lineBuf) && raceCount < RACES) {
    if (!isdigit(lineBuf[i])) {
      i++;
      continue;
    }

    char numberBuf[16];
    size_t j = 0;
    while (isdigit(lineBuf[i])) {
      numberBuf[j++] = lineBuf[i++];
    }
    numberBuf[j] = '\0';

    races[raceCount++].distance = atoi(numberBuf);
  }

  return 0;
}

/**
 * Cacluate number of different ways to win a race.
 *
 * @param race - an instance of a race.
 * @return - number of ways to win the race.
 */
size_t getWinningPermutations(Race *race) {
  size_t winningPermutations = 0;

  size_t timeCharging = 0;
  while (timeCharging < race->time) {
    size_t timeRacing = race->time - timeCharging;
    size_t distance = timeRacing * (timeCharging * RATE);

    if (distance > race->distance) {
      winningPermutations++;
    }

    timeCharging++;
  }

  return winningPermutations;
}

int main(void) { 
  Race races[RACES] = {0};
  if (getRaces(races)) {
    return 1;
  }

  size_t answer = 1;
  for (size_t i = 0; i < RACES; ++i) {
    answer *= getWinningPermutations(&races[i]);
  }

  printf("Answer: %lu\n", answer);

  return 0; 
}
