#include "errorCat.h"

void errorNoSuchFileOrDir(char *filename) {
  printf("cat: %s: No such file or directory", filename);
}

void errorInvalidOptions(char flag) {
  printf("cat: invalid option -- '%c'\nUsage: cat [OPTION]... [FILE]...", flag);
}
