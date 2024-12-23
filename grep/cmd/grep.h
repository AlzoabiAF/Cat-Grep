#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#include "../common.h"
#include "./../internal/error/errorGrep.h"
#include "./../internal/print/print.h"

bool isFile(char *filename);

void start(int argc, char *arcv[]);
void parseFlags(Options *flags, int argc, char *argv[], char **pattern,
                int *sizePattern, int *capacity);
bool savingPattern(char **pattern, int *sizePattern, char *arg, char opt,
                   int *capacity);
bool savingPatternsFile(char **pattern, int *sizePattern, char *filename,
                        int *capacity);
void clearMemory(char **pattern, int sizePattern);

#endif