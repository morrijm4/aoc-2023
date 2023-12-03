#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 512

typedef struct {
  int r_cubes;
  int g_cubes;
  int b_cubes;
} cube_set_t;

cube_set_t find_min_cube_set(char *buf) {
  cube_set_t min_cube_set = {0};

  // loop past game id
  while (*buf++ != ':') {
  }

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
      switch (*++buf) {
      case 'r':
	if (min_cube_set.r_cubes < num_cubes) {
	  min_cube_set.r_cubes = num_cubes;
	}
	break;
      case 'g':
	if (min_cube_set.g_cubes < num_cubes) {
	  min_cube_set.g_cubes = num_cubes;
	}
	break;
      case 'b':
	if (min_cube_set.b_cubes < num_cubes) {
	  min_cube_set.b_cubes = num_cubes;
	}
	break;
      default:
        printf("Unexpected color %c\n", *buf);
        exit(1);
      }
    }
  }

  return min_cube_set;
}

int calculate_power_of_set(cube_set_t set) {
  return set.r_cubes * set.g_cubes * set.b_cubes;
}

int main(void) {
  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  char buf[BUF_SIZE];
  int total = 0;

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    total += calculate_power_of_set(find_min_cube_set(buf));
  }

  printf("Answer: %d\n", total);

  fclose(fp);
  return 0;
}
