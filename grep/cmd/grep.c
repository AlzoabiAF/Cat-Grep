#include "grep.h"

// to run grep
void start(int argc, char *argv[]) {
  Options flags = {0};
  int capacity = 4;
  char *filename, **pattern = malloc(capacity * sizeof(char *));
  int sizePattern = 0;
  opterr = 0;
  parseFlags(&flags, argc, argv, pattern, &sizePattern, &capacity);
  // reading pattern if there are no options f and e
  if (!(flags.e || flags.f)) {
    if (optind < argc)
      savingPattern(pattern, &sizePattern, argv[optind++], '\0', &capacity);
    else {
      clearMemory(pattern, sizePattern);
      errorNoExistsPatterns('\0');
      exit(1);
    }
  }

  //  do not output the filename if there is only one or if option l = true
  if (argc - optind == 1) {
    flags.h = true;
  }

  // the file name is read
  while (optind < argc) {
    filename = argv[optind++];
    if (isFile(filename)) {
      print(&flags, pattern, sizePattern, filename);
    } else if (!flags.s) {
      errorNoSuchFileOrDir(filename);
    }
  }

  // if the files are not being transferred
  if (!filename && !flags.s) errorNoSuchFileOrDir("");

  clearMemory(pattern, sizePattern);
}

// flag parsing
void parseFlags(Options *flags, int argc, char *argv[], char **pattern,
                int *sizePattern, int *capacity) {
  char opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        if (!optarg) {
          errorNoExistsPatterns(opt);
          exit(1);
        }
        flags->e = savingPattern(pattern, sizePattern, optarg, 'e', capacity);
        break;
      case 'i':
        flags->i = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'c':
        flags->c = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'f':
        flags->f = savingPatternsFile(pattern, sizePattern, optarg, capacity);
        break;
      case 'o':
        flags->o = true;
        break;
      case '?':
        errorUnknownOption(optopt);
        exit(1);
    }
  }
}

// saving the pattern
bool savingPattern(char **pattern, int *sizePattern, char *arg, char opt,
                   int *capacity) {
  bool is_valid = false;
  if (*sizePattern >= *capacity) {
    (*capacity) *= 2;
    pattern = realloc(pattern, *capacity * sizeof(char *));
  }
  pattern[*sizePattern] = (char *)malloc(strlen(arg) + 2);
  if (pattern[*sizePattern]) {
    strcpy(pattern[*sizePattern], arg);
    int len = strlen(pattern[*sizePattern]);
    pattern[*sizePattern][len] = opt;
    pattern[*sizePattern][len + 1] = '\0';
    (*sizePattern)++;
    is_valid = true;
  }
  return is_valid;
}

// saves the file where the patterns are stored (for options f)
bool savingPatternsFile(char **pattern, int *sizePattern, char *filename,
                        int *capacity) {
  bool is_valid = false;
  if (isFile(filename)) {
    savingPattern(pattern, sizePattern, filename, 'f', capacity);
    is_valid = true;
  } else {
    errorNoSuchFileOrDir(filename);
    exit(1);
  }
  return is_valid;
}

// check for the existence of a file
bool isFile(char *filename) {
  FILE *file = fopen(filename, "r");
  bool flag = false;
  if (file) {
    flag = true;
    fclose(file);
  }
  return flag;
}

void clearMemory(char **pattern, int sizePattern) {
  for (int i = 0; i < sizePattern; ++i) free(pattern[i]);
  free(pattern);
}