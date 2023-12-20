#include <ctype.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SeedPair {
  uint64_t start;
  uint64_t range;
} SeedPair;

static int64_t *seeds;
static int64_t *newSeeds;
static uint64_t numberOfSeeds = 0;

static void init() {
  for (size_t i = 0; i < numberOfSeeds; ++i) {
    newSeeds[i] = -1;
  }
}

// param: seed pair array
static void getSeedPairs(char *line, size_t lineSize, SeedPair *pairs,
                         size_t pairsSize) {
  // start: 1
  // range: 0
  size_t startOrRange = 1;

  size_t pairCount = 0;
  size_t i = 0;

  while (line[i] != '\n' && i < lineSize && pairCount < pairsSize) {
    if (!isdigit(line[i])) {
      i++;
      continue;
    }

    char buf[32];
    size_t j = 0;
    while (isdigit(line[i])) {
      buf[j++] = line[i++];
    }
    buf[j] = '\0';

    if (startOrRange) {
      pairs[pairCount].start = strtoll(buf, NULL, 10);
    } else {
      pairs[pairCount].range = strtoll(buf, NULL, 10);
      pairCount++;
    }

    startOrRange = !startOrRange;
  }
}

static void printSeedPairs(SeedPair *pairs, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    printf("Pair\n");
    printf("Start: %lld\n", pairs[i].start);
    printf("Range: %lld\n", pairs[i].range);
    printf("\n");
  }
}

static void calculateSeeds(SeedPair *pairs, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    numberOfSeeds += pairs[i].range;
  }

  seeds = (int64_t *)malloc(sizeof(int64_t) * numberOfSeeds);

  if (seeds == NULL) {
    perror("error allocating memory");
    exit(1);
  }

  size_t seedNumber = 0;
  size_t rangeNumber = 0;
  size_t pairNumber = 0;
  while (seedNumber < numberOfSeeds) {
    seeds[seedNumber++] = pairs[pairNumber].start + rangeNumber;

    if (rangeNumber < pairs[pairNumber].range - 1) {
      rangeNumber++;
    } else {
      rangeNumber = 0;
      pairNumber++;
    }
  }

  newSeeds = (int64_t *)malloc(sizeof(int64_t) * numberOfSeeds);

  if (seeds == NULL) {
    perror("error allocating memory");
    exit(1);
  }

  for (size_t i = 0; i < numberOfSeeds; ++i) {
    newSeeds[i] = -1;
  }
}

static void printSeeds() {
  size_t i = 0;
  while (i < numberOfSeeds - 1) {
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

  for (size_t i = 0; i < numberOfSeeds; ++i) {
    if (seeds[i] >= sourceStart && seeds[i] < sourceEnd) {
      int64_t diff = seeds[i] - sourceStart;
      newSeeds[i] = map.destinationRangeStart + diff;
    }
  }
}

static void commitSeeds() {
  for (size_t i = 0; i < numberOfSeeds; ++i) {
    if (newSeeds[i] != -1) {
      seeds[i] = newSeeds[i];
    }
  }
  init();
}

static void printLowest() {
  int64_t min = -1;
  for (size_t i = 0; i < numberOfSeeds; ++i) {
    if (min == -1) {
      min = seeds[i];
    } else if (seeds[i] < min) {
      min = seeds[i];
    }
  }

  printf("Answer: %lld\n", min);
}

static void clean() {
  free(seeds);
  free(newSeeds);
}
