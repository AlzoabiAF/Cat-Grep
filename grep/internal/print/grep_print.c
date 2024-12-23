#include "print.h"

// checking for missing options
bool isNoOptions(Options *flags) {
  return flags->e == false && flags->i == false && flags->v == false &&
         flags->c == false && flags->l == false && flags->n == false &&
         flags->s == false && flags->f == false && flags->o == false &&
         flags->h == false;
}

// running the basic grep logic
void print(Options *flags, char **patterns, int sizePattern, char *filename) {
  if (isNoOptions(flags)) {
    printWithoutOptions(patterns, filename);
  } else {
    printWithOptions(flags, patterns, sizePattern, filename);
  }
}

// finding patterns in a file and display the found lines on the screen, if
// there is NO options
void printWithoutOptions(char **patterns, char *filename) {
  FILE *file = fopen(filename, "r");
  size_t len;
  char *line = NULL;
  while (getline(&line, &len, file) != -1) {
    line[strcspn(line, "\n")] = '\0';
    if (strstr(line, patterns[0])) {
      printf("%s:%s\n", filename, line);
    }
  }
  free(line);
  fclose(file);
}

// finding patterns in a file and display the found lines on the screen, if
// there are options
void printWithOptions(Options *flags, char **patterns, int sizePatterns,
                      char *filename) {
  FILE *file = fopen(filename, "r");
  size_t len, counterValidLine = 0, lineNumber = 0;
  char *line = NULL;
  bool is_valid = false;

  while (getline(&line, &len, file) != -1) {
    lineNumber++;
    line[strcspn(line, "\n")] = '\0';
    // if (!strlen(line)) continue;
    is_valid = isTherePattern(flags, patterns, sizePatterns, line);
    if (is_valid) {
      printFormattedString(flags, patterns, sizePatterns, line, filename,
                           lineNumber, &counterValidLine);
      if (flags->l) break;
    }
  }

  printCounterValidString(flags, filename, counterValidLine);
  free(line);
  fclose(file);
}

// checking for patterns in a string
bool isTherePattern(Options *flags, char **patterns, int sizePattern,
                    char *line) {
  int len;
  char opt, *pattern;
  bool is_valid = false;

  if (flags->e || flags->f) {
    for (int i = 0; i < sizePattern && !is_valid; ++i) {
      pattern = patterns[i];
      len = strlen(pattern);
      opt = pattern[len - 1];
      pattern[len - 1] = '\0';
      if (opt == 'e') {
        is_valid =
            searchingPatternInTheLine(&line, pattern, flags->i, flags->v);
      } else {
        is_valid = isTherePatternsFromFile(line, pattern, flags->i, flags->v);
      }

      pattern[len - 1] = opt;
    }
  } else {
    pattern = patterns[sizePattern - 1];
    is_valid = searchingPatternInTheLine(&line, pattern, flags->i, flags->v);
  }

  return is_valid;
}

// checking for only one pattern in a string
char *searchingPatternInTheLine(char **line, char *pattern, bool flag_i,
                                bool flag_v) {
  regex_t regex;
  regmatch_t match;
  char *match_result = NULL;
  int flags = REG_EXTENDED | (flag_i ? REG_ICASE : 0);

  if (regcomp(&regex, pattern, flags) == 0) {
    int result = regexec(&regex, *line, 1, &match, 0);

    if ((!result && !flag_v) || (result && flag_v)) {
      match_result = *line + match.rm_so;
      *line += match.rm_eo;
    }
  }
  regfree(&regex);
  return match_result;
}

// checking for regexes from a file in a string
bool isTherePatternsFromFile(char *line, char *filename, bool flag_i,
                             bool flag_v) {
  FILE *file = fopen(filename, "r");
  char *regex_pattern = NULL;
  size_t len;
  bool match_found = false;
  while (getline(&regex_pattern, &len, file) != -1) {
    regex_pattern[strcspn(regex_pattern, "\n")] = '\0';
    if (!strlen(regex_pattern) && flag_v) {
      match_found = false;
      break;
    }
    match_found =
        searchingPatternInTheLine(&line, regex_pattern, flag_i, flag_v) ||
        match_found;
  }
  free(regex_pattern);
  fclose(file);
  return match_found;
}

// output of a formatted string
void printFormattedString(Options *flags, char **patterns, int sizePatterns,
                          char *line, char *filename, size_t lineNumber,
                          size_t *counterValidLine) {
  if (flags->l)
    printf("%s\n", filename);
  else if (flags->c)
    (*counterValidLine)++;
  else if (!flags->o)
    printInfoLineAndLine(flags, line, filename, lineNumber, 0);
  else if (!flags->v)
    printForrmattedStringWithO(flags, patterns, sizePatterns, line, filename,
                               lineNumber);
}

// for option c
void printCounterValidString(Options *flags, char *filename,
                             size_t counterValidLine) {
  if (!flags->l && flags->c) {
    if (flags->h)
      printf("%ld\n", counterValidLine);
    else
      printf("%s:%ld\n", filename, counterValidLine);
  }
}

// output of a formatted string if there is option 'o'
void printForrmattedStringWithO(Options *flags, char **patterns,
                                int sizePatterns, char *line, char *filename,
                                size_t lineNumber) {
  char opt, *pattern;
  size_t len;
  if (flags->e || flags->f) {
    for (int i = 0; i < sizePatterns; ++i) {
      pattern = patterns[i];
      len = strlen(pattern);
      opt = pattern[len - 1];
      pattern[len - 1] = '\0';
      if (opt == 'e') {
        processAndPrintMatchingSubstrings(flags, &line, patterns[i], filename,
                                          lineNumber);
      } else {
        processPatternsFromFile(flags, &line, patterns[i], filename,
                                lineNumber);
      }
      pattern[len - 1] = opt;
    }
  } else {
    processAndPrintMatchingSubstrings(flags, &line, patterns[0], filename,
                                      lineNumber);
  }
}

void processAndPrintMatchingSubstrings(Options *flags, char **line,
                                       char *pattern, char *filename,
                                       int lineNumber) {
  char *foundSubstring =
      searchingPatternInTheLine(line, pattern, flags->i, flags->v);
  while (foundSubstring) {
    printInfoLineAndLine(flags, foundSubstring, filename, lineNumber,
                         strlen(pattern));
    foundSubstring =
        searchingPatternInTheLine(line, pattern, flags->i, flags->v);
  }
}

void processPatternsFromFile(Options *flags, char **line, char *pattern,
                             char *filename, int lineNumber) {
  FILE *file = fopen(pattern, "r");
  char *regex_pattern = NULL;
  size_t len;
  while (getline(&regex_pattern, &len, file) != -1) {
    regex_pattern[strcspn(regex_pattern, "\n")] = '\0';
    if (strlen(regex_pattern))
      processAndPrintMatchingSubstrings(flags, line, regex_pattern, filename,
                                        lineNumber);
  }
  free(regex_pattern);
  fclose(file);
}

// prints the file name, line number and valid string if the options allow
void printInfoLineAndLine(Options *flags, char *line, char *filename,
                          size_t lineNumber, int sizeSubstring) {
  if (!flags->h) printf("%s:", filename);
  if (flags->n) printf("%ld:", lineNumber);
  if (flags->o)
    printf("%.*s\n", sizeSubstring, line);
  else
    printf("%s\n", line);
}
