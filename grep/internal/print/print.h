#ifndef PRINT_H
#define PRINT_H

#define _GNU_SOURCE
#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common.h"

bool isNoOptions(Options *flags);

void print(Options *flags, char **patterns, int sizePatterns, char *filename);
void printWithoutOptions(char **patterns, char *filename);
void printWithOptions(Options *flags, char **patterns, int sizePatterns,
                      char *filename);
bool isTherePattern(Options *flags, char **patterns, int sizePatterns,
                    char *line);
char *searchingPatternInTheLine(char **line, char *pattern, bool flag_i,
                                bool flag_v);
bool isTherePatternsFromFile(char *line, char *filename, bool flag_i,
                             bool flag_v);
void printFormattedString(Options *flags, char **patterns, int sizePatterns,
                          char *line, char *filename, size_t lineNumber,
                          size_t *counterValidLine);
void printCounterValidString(Options *flags, char *filename,
                             size_t counterValidLine);
void printForrmattedStringWithO(Options *flags, char **patterns,
                                int sizePatterns, char *line, char *filename,
                                size_t lineNumber);
void processAndPrintMatchingSubstrings(Options *flags, char **line,
                                       char *pattern, char *filename,
                                       int lineNumber);
void processPatternsFromFile(Options *flags, char **line, char *pattern,
                             char *filename, int lineNumber);
void printInfoLineAndLine(Options *flags, char *line, char *filename,
                          size_t lineNumber, int sizeSubstring);
#endif