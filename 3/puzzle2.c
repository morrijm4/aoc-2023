#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} point_t;

point_t buildPoint() {
  point_t p = {
      .x = -1,
      .y = -1,
  };
  return p;
}

int isPointEmpty(point_t p) { return p.y == -1 && p.x == -1; }

int equalPoints(point_t a, point_t b) { return a.x == b.x && a.y == b.y; }

typedef struct {
  char **grid_ptr;
  // grid * -> * -> chars
  //           * -> chars
  //           * -> chars
  //           * -> chars
  int cols;
  int rows;
} grid_t;

void freeGrid(grid_t grid) {
  for (int i = 0; i < grid.rows; ++i) {
    free(grid.grid_ptr[i]);
  }
  free(grid.grid_ptr);
}

grid_t buildGrid() {
  char buf[256];
  char ch;
  grid_t grid = {0};
  FILE *fp = fopen("input.txt", "r");

  if (fp == NULL) {
    perror("Error opening file");
    exit(1);
  }

  // calculate width
  while ((ch = fgetc(fp) != '\n')) {
    grid.cols++;
  }

  // calculate height
  grid.rows = 1;
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    grid.rows++;
  }

  // Allocate memory for grid
  grid.grid_ptr = (char **)malloc(grid.rows * sizeof(char *));
  if (grid.grid_ptr == NULL) {
    perror("Memory allocation error with rows");
    exit(1);
  }

  for (int i = 0; i < grid.rows; ++i) {
    grid.grid_ptr[i] = (char *)malloc(grid.cols * sizeof(char));
    if (grid.grid_ptr[i] == NULL) {
      perror("Memory allocation error width cols");
      exit(1);
    }
  }

  fclose(fp);
  return grid;
}

void initGrid(grid_t grid) {
  char buf[256];

  FILE *fp = fopen("input.txt", "r");
  if (fp == NULL) {
    perror("Error opening file");
    exit(1);
  }

  int i = 0;
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    for (int j = 0; j < grid.cols; ++j) {
      grid.grid_ptr[i][j] = buf[j];
    }
    i++;
  }

  fclose(fp);
}

int calculateRatio(grid_t grid, point_t a, point_t b) {
  char num1[4];
  char num2[4];
  int i = 0;

  while (isdigit(grid.grid_ptr[a.y][a.x])) {
    num1[i++] = grid.grid_ptr[a.y][a.x++];
  }
  num1[i] = '\0';

  i = 0;
  while (isdigit(grid.grid_ptr[b.y][b.x])) {
    num2[i++] = grid.grid_ptr[b.y][b.x++];
  }
  num2[i] = '\0';

  return atoi(num1) * atoi(num2);
}

point_t findNumberBeginning(grid_t grid, int y, int x) {
  while (x > 0 && isdigit(grid.grid_ptr[y][x - 1])) {
    x--;
  }

  point_t p = {
      .x = x,
      .y = y,
  };

  return p;
}

int getGearRatio(grid_t grid, int y, int x) {
  point_t p1 = buildPoint();
  point_t p2 = buildPoint();

  int i = y == 0 ? 0 : -1;
  int i_end = y == grid.rows - 1 ? 0 : 1;
  int j_end = x == grid.cols - 1 ? 0 : 1;

  while (i <= i_end) {
    int j = x == 0 ? 0 : -1;
    while (j <= j_end) {

      char ch = grid.grid_ptr[y + i][x + j];
      if (isdigit(ch)) {
        point_t p = findNumberBeginning(grid, y + i, x + j);

        if (isPointEmpty(p1) || equalPoints(p1, p)) {
          p1 = p;
        } else if (isPointEmpty(p2) || equalPoints(p2, p)) {
          p2 = p;
        } else {
          return 0; // more than two parts around the gear
        }
      }
      j++;
    }
    i++;
  }

  if (isPointEmpty(p1) || isPointEmpty(p2)) {
    return 0; // less than two parts around the gear
  }

  return calculateRatio(grid, p1, p2);
}

int main(void) {
  int ans = 0;
  grid_t grid = buildGrid();
  initGrid(grid);

  for (int y = 0; y < grid.rows; ++y) {
    for (int x = 0; x < grid.cols; ++x) {
      if (grid.grid_ptr[y][x] == '*') {
        ans += getGearRatio(grid, y, x);
      }
    }
  }

  printf("Answer: %d\n", ans);

  freeGrid(grid);
  return 0;
}
