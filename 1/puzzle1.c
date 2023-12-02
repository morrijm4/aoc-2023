#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BUF_SIZE 512

int getCalibrationValue(char *buf) {
  char str[3];
  str[2] = '\0';

  // get first digit char
  size_t i = 0;
  while (buf[i] != '\0') {
    if (isdigit(buf[i])) {
      str[0] = buf[i];
      break;
    } 
    ++i;
  }

  // get last digit char
  while (buf[i] != '\0') {
    if (isdigit(buf[i])) {
      str[1] = buf[i];
    }
    ++i;
  }
  
  // ascii to int
  return atoi(str);
}

int main(void) {
  FILE *fp;
  char buf[BUF_SIZE];
  int total = 0;

  fp = fopen("input.txt", "r");

  if (fp == NULL) {
    perror("Error opening file");
    return 1;
  }

  while (fgets(buf, sizeof(buf), fp) != NULL) {
    total += getCalibrationValue(buf);
  }

  printf("%d", total);

  return 0;
}
