#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define MAX_STRINGS 9
#define MAX_STRING_SIZE 6
#define ASCII_NUMBER_OFFSET 49

// Returns the ascii representation of the integer value of the buffer if it 
// begins with the english spelling of the integer. Otherwise returns 0.
int getTextDigit(char *buf) {
  static char numbers[MAX_STRINGS][MAX_STRING_SIZE] = {
      "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

  for (size_t i = 0; i < MAX_STRINGS; ++i) {
    size_t j = 0;
    while (buf[j] != '\0' && j < MAX_STRING_SIZE) {
      if (buf[j] != numbers[i][j]) {
        break;
      }

      if (numbers[i][j + 1] == '\0') {
        return i + ASCII_NUMBER_OFFSET;
      }
      ++j;
    }
  }

  return 0;
}

int getCalibrationValue(char *buf) {
  int textNumber;
  char str[3];
  str[2] = '\0';

  // get first digit char
  size_t i = 0;
  while (buf[i] != '\0') {
    if (isdigit(buf[i])) {
      str[0] = buf[i];
      break;
    }

    textNumber = getTextDigit(buf + i);
    if (textNumber) {
      str[0] = (char)textNumber;    
      ++i;
      break;
    }
    ++i;
  }

  // get last digit char
  while (buf[i] != '\0') {
    if (isdigit(buf[i])) {
      str[1] = buf[i];
    }

    textNumber = getTextDigit(buf + i);
    if (textNumber) {
      str[1] = (char)textNumber;    
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
