#ifndef S21_CAT_H_
#define S21_CAT_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../internal/error/errorCat.h"
#include "../internal/print/print.h"
#include "../options.h"

void start(int argc, char *arcv[]);
bool isFlags(char *flag);
void isFile(char *file);
void parseFlags(Options *flags, char *strFlag);
bool parseFlagsGNU(Options *flags, char *strFlag);

#endif