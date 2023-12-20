#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define RATE 1

typedef struct Race {
  uint64_t time;
  uint64_t distance;
} Race;

void printRace(Race *race) {
  printf("Time: %llu\n", race->time);
  printf("Distance: %llu\n", race->distance);
  printf("\n");
}

/**
 * Cacluate number of different ways to win a race.
 *
 * @param race - an instance of a race.
 * @return - number of ways to win the race.
 */
uint64_t getWinningPermutations(Race *race) {
  uint64_t winningPermutations = 0;

  uint64_t timeCharging = 0;
  while (timeCharging < race->time) {
    uint64_t timeRacing = race->time - timeCharging;
    uint64_t distance = timeRacing * (timeCharging * RATE);

    if (distance > race->distance) {
      winningPermutations++;
    }

    timeCharging++;
  }

  return winningPermutations;
}

uint64_t combineNumbersInBuffer(char *buffer) {
  char number[64];
  size_t i = 0;
  while (*buffer != '\n') {
    if (isdigit(*buffer)) {
      number[i++] = *buffer;
    }
    buffer++;
  }
  number[i] = '\0';

  return strtoull(number, NULL, 10);
}

/**
 * Parse input.txt file to create Race struct.
 *
 * @param race - reference to race struct to write to.
 */
void parseRace(Race *race) {
  FILE *file_pointer = fopen("input.txt", "r");
  if (file_pointer == NULL) {
    perror("unable to open file");
  }

  char line[64];
  if (fgets(line, sizeof(line), file_pointer) == NULL) {
    printf("error reading line");
    exit(EXIT_FAILURE);
  }
  race->time = combineNumbersInBuffer(line);

  if (fgets(line, sizeof(line), file_pointer) == NULL) {
    printf("error reading line");
    exit(EXIT_FAILURE);
  }
  race->distance = combineNumbersInBuffer(line);

  fclose(file_pointer);
}

int main(void) {
  Race race = {0};
  parseRace(&race);

  printRace(&race);

  uint64_t answer = getWinningPermutations(&race);

  printf("Answer: %llu\n", answer);

  return 0;
}
