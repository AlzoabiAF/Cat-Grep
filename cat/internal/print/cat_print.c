#include "print.h"

bool isTab(char c) { return (c == '\t'); }

bool isNewLine(char c) { return (c == '\n'); }

void printTabsNumber(int *number) { printf("%6d\t", (*number)++); }

bool isNoOptions(Options *flags) {
  return flags->b == false && flags->e == false && flags->n == false &&
         flags->s == false && flags->t == false && flags->v == false;
}

void print_char(unsigned char c, Options *options) {
  if (options->v) {
    if (isTab(c) && !options->t) {
      printf("%c", c);
    } else if (isNewLine(c)) {
      if (options->e)
        printf("$\n");
      else
        printf("\n");
    } else if (c < 32) {
      printf("^%c", c + 64);
    } else if (c == 127) {
      printf("^?");
    } else if (c > 127 && c < 160) {
      printf("M-^%c", c - 64);
    } else if (c >= 160) {
      printf("M-%c", c - 128);
    } else {
      printf("%c", c);
    }
  } else if (options->t && isTab(c)) {
    printf("^I");
  } else if (isNewLine(c) && options->e) {
    printf("$\n");
  } else {
    printf("%c", c);
  }
}

void printWithOptions(Options *options, char *filename) {
  FILE *file = fopen(filename, "r");
  bool flagNewLine = true;
  int counterNewLine = 1;
  char c = fgetc(file);
  int numbers = 1;

  while (c != EOF) {
    if (flagNewLine) {
      if (options->s && counterNewLine + isNewLine(c) > 2) {
        c = fgetc(file);
        continue;
      } else if (options->b) {
        if (!isNewLine(c)) printTabsNumber(&numbers);
      } else if (options->n)
        printTabsNumber(&numbers);
    }

    print_char(c, options);

    flagNewLine = isNewLine(c);
    if (flagNewLine) {
      ++counterNewLine;
    } else {
      counterNewLine = 0;
    }
    c = fgetc(file);
  }
  fclose(file);
}

void printWitoutOptions(char *filename) {
  FILE *file = fopen(filename, "rt");

  int c = fgetc(file);
  while (c != EOF) {
    putc(c, stdout);
    c = fgetc(file);
  }
  fclose(file);
}

void print(char *filename, Options *flags) {
  if (isNoOptions(flags)) {
    printWitoutOptions(filename);
  } else {
    printWithOptions(flags, filename);
  }
}