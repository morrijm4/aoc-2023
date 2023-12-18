#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SEEDS 4
#define BUFFER_SIZE 265

FILE *file_p;

void readFirstLine(char *buf) {
  if (fgets(buf, BUFFER_SIZE, file_p) != NULL) {
    // parse seeds
  } else if (feof(file_p)) {
    printf("End of file...");
  } else if (ferror(file_p)) {
    perror("error reading first line");
  } else {
    printf("unknown behavior");
  }
}

void printSeeds(uint64_t *seeds) {
  size_t i = 0; 
  while (i < SEEDS - 1) {
    printf("%llu, ", seeds[i++]);
  }
  printf("%llu\n", seeds[i]);
}

uint64_t parseSeed(char **buf) {
  char *str = *buf;
  char num[64] = {0};
  size_t i = 0;

  while (*str != ' ') {
    num[i++] = *str++; 
  }

  *buf += i;

  uint64_t tmp = (uint64_t)atoi(num);
  printf("%llu\n", tmp); 
  return tmp;
}

void parseSeeds(char *buf, uint64_t *seeds) {
  // move ptr to first digit
  buf += 8;

  size_t i = 0;
  while (*buf != '\n' && i < SEEDS) {
    if (isdigit(*buf)) {
      seeds[i++] = parseSeed(&buf);
    } else {
      buf++;
    }
  }
  printSeeds(seeds);
}

int main(void) {
  uint64_t seeds[SEEDS] = {0};

  printSeeds(seeds);

  file_p = fopen("input.txt", "r");
  if (file_p == NULL) {
    perror("unable to open file");
  }

  char buf[BUFFER_SIZE];
  readFirstLine(buf);
  parseSeeds(buf, seeds);
  printSeeds(seeds);

  while (fgets(buf, sizeof(buf), file_p) != NULL) {
    // printf("%s", buf);
  }

  if (ferror(file_p)) {
    perror("error reading file");
  }

  return 0;
}
