#ifndef ERROR_CAT_H
#define ERROR_CAT_H

#include <stdio.h>

void errorNoSuchFileOrDir(char *filename);
void errorNoExistsPatterns(char opt);
void errorUnknownOption(char opt);

#endif