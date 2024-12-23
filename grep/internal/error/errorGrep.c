#include "errorGrep.h"

void errorNoSuchFileOrDir(char *filename) {
  printf("grep: %s: No such file or directory\n", filename);
}

void errorNoExistsPatterns(char opt) {
  printf(
      "grep: option requires an argument -- '%c'\nUsage: grep [OPTION]... "
      "PATTERNS [FILE]...\nTry 'grep --help' for more information.\n",
      opt);
}

void errorUnknownOption(char opt) {
  printf(
      "grep: option requires an argument -- '%c'\nUsage: grep [OPTION]... "
      "PATTERNS [FILE]...\nTry 'grep --help' for more information.\n",
      opt);
}