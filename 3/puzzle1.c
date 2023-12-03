#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

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

int isPartNumber(grid_t grid, int y, int x) {
  if (!isdigit(grid.grid_ptr[y][x])) {
    return 0;
  }

  if (x > 0) {
    char left = grid.grid_ptr[y][x - 1];
    if (left != '.' && !isdigit(left)) {
      return 1;
    }

    if (y > 0) {
      char top_left = grid.grid_ptr[y - 1][x - 1];
      if (top_left != '.' && !isdigit(top_left)) {
        return 1;
      }
    }

    if (y < grid.rows - 1) {
      char bottom_left = grid.grid_ptr[y + 1][x - 1];
      if (bottom_left != '.' && !isdigit(bottom_left)) {
        return 1;
      }
    }
  }

  while (isdigit(grid.grid_ptr[y][x])) {
    if (y > 0) {
      char top = grid.grid_ptr[y - 1][x];
      if (top != '.' && !isdigit(top)) {
        return 1;
      }
    }

    if (y < grid.rows - 1) {
      char bottom = grid.grid_ptr[y + 1][x];
      if (bottom != '.' && !isdigit(bottom)) {
        return 1;
      }
    }

    if (!(++x < grid.cols)) {
      return 0;
    }
  }

  char right = grid.grid_ptr[y][x];
  if (right != '.' && !isdigit(right)) {
    return 1;
  }

  if (y > 0) {
    char top_right = grid.grid_ptr[y - 1][x];
    if (top_right != '.' && !isdigit(top_right)) {
      return 1;
    }
  }

  if (y < grid.rows - 1) {
    char bottom_right = grid.grid_ptr[y + 1][x];
    if (bottom_right != '.' && !isdigit(bottom_right)) {
      return 1;
    }
  }

  return 0;
}



int main(void) {
  int ans = 0;
  grid_t grid = buildGrid();
  initGrid(grid);

  for (int y = 0; y < grid.rows; ++y) {
    for (int x = 0; x < grid.cols; ++x) {
      if (isPartNumber(grid, y, x)) {
	char number[4];
	int i = 0;
        while (isdigit(grid.grid_ptr[y][x])) {
          number[i++] = grid.grid_ptr[y][x++];
        }
	number[i] = '\0';

	ans += atoi(number);
      }
    }
  }

  printf("Answer: %d\n", ans);

  freeGrid(grid);
  return 0;
}
