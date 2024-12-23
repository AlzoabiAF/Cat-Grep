#include "s21_cat.h"

#if defined(__gnu_linux__) || defined(__linux__)
#define GNU 1
#else
#define GNU 0
#endif

void start(int argc, char *arcv[]) {
  Options flags = {0};

  int i;
  for (i = 1; i < argc; ++i) {
    if (isFlags(arcv[i]))
      parseFlags(&flags, arcv[i]);
    else {
      break;
    }
  }

  if (i == argc) {
    errorNoSuchFileOrDir("");
    exit(2);
  }

  for (; i < argc; ++i) {
    isFile(arcv[i]);
    print(arcv[i], &flags);
  }
}

bool isFlags(char *flag) { return flag[0] == '-'; }

void isFile(char *filename) {
  FILE *file = fopen(filename, "r");
  if (file) {
    fclose(file);

  } else {
    errorNoSuchFileOrDir(filename);
    exit(2);
  }
}

void parseFlags(Options *flags, char *strFlag) {
#if GNU
  if (parseFlagsGNU(flags, strFlag)) {
    return;
  }
#endif

  for (int i = 1; strFlag[i] != '\0'; ++i) {
    switch (strFlag[i]) {
      case 'b':
        flags->b = true;
        break;
      case 'e':
        flags->e = true;
        flags->v = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 't':
        flags->t = true;
        flags->v = true;
        break;
      case 'v':
        flags->v = true;
        break;
#if GNU
      case 'E':
        flags->e = true;
        break;
      case 'T':
        flags->t = true;
        break;
#endif
      default:
        errorInvalidOptions(strFlag[i]);
        exit(1);
    }
  }
}

bool parseFlagsGNU(Options *flags, char *strFlag) {
  bool flag = false;
  if (!strcmp(strFlag, "--number-nonblank")) {
    flags->b = true;
    flag = true;
  } else if (!strcmp(strFlag, "--number")) {
    flags->n = true;
    flag = true;
  } else if (!strcmp(strFlag, "--squeeze-blank")) {
    flags->s = true;
    flag = true;
  }
  return flag;
}