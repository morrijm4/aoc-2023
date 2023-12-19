#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SEEDS 20

static int64_t seeds[SEEDS];
static int64_t newSeeds[SEEDS];

static void init() {
  for (size_t i = 0; i < SEEDS; ++i) {
    newSeeds[i] = -1;
  }
}

static int64_t *getSeeds(char *firstLine) {
  size_t seedCount = 0;

  // ex: seeds: 79 14 55 13
  char buf[32];
  while (*firstLine != '\n' && seedCount < SEEDS) {
    if (isdigit(*firstLine)) {
      size_t i = 0;

      while (isdigit(*firstLine)) {
	buf[i++] = *firstLine++;	
      }
      buf[i] = '\0';
      
      seeds[seedCount++] = strtoull(buf, NULL, 10);
    } else {
      firstLine++;
    }
  }

  return seeds;
}

static void printSeeds() {
  size_t i = 0;
  while (i < SEEDS - 1) {
    printf("%lld, ", seeds[i++]);
  }
  printf("%lld\n", seeds[i]);
}

typedef struct Map {
  int64_t destinationRangeStart;
  int64_t sourceRangeStart;
  int64_t rangeLength;
} Map;

static void printMap(Map map) {
  printf("Destination range start:  %lld\n", map.destinationRangeStart);
  printf("Source range start:       %lld\n", map.sourceRangeStart);
  printf("Range length:             %lld\n", map.rangeLength);
  printf("\n");
}

static Map parseMap(char *line) {
  Map map = {0};
  size_t count = 0;

  // ex: 50 98 2
  char buf[32];
  while (*line != '\n' && count < 3) {
    if (!isdigit(*line)) {
      line++;
      continue;
    }

    size_t i = 0;
    while (isdigit(*line)) {
      buf[i++] = *line++;
    }
    buf[i] = '\0';

    switch (count++) {
      case 0:
	map.destinationRangeStart = strtoull(buf, NULL, 10);
	break; 
      case 1:
	map.sourceRangeStart = strtoull(buf, NULL, 10);
	break; 
      case 2:
	map.rangeLength = strtoull(buf, NULL, 10);
	break; 
      default:
	printf("Unknown state.\n");
	exit(1);
    }
  }

  return map;
}

static void interpretMap(Map map) {
  int64_t sourceStart = map.sourceRangeStart;
  int64_t sourceEnd = map.sourceRangeStart + map.rangeLength;

  for (size_t i = 0; i < SEEDS; ++i) {
    if (seeds[i] >= sourceStart && seeds[i] < sourceEnd) {
      int64_t diff = seeds[i] - sourceStart;
      newSeeds[i] = map.destinationRangeStart + diff;
    }
  }
}

static void commitSeeds() {
  for (size_t i = 0; i < SEEDS; ++i) {
    if (newSeeds[i] != -1) {
      seeds[i] = newSeeds[i];
    }
  }
  init();
}

static void printLowest() {
  int64_t min = -1;
  for (size_t i = 0; i < SEEDS; ++i) {
    if (min == -1) {
      min = seeds[i];
    } else if (seeds[i] < min) {
      min = seeds[i];
    }
  }

  printf("Answer: %lld\n", min);
}
