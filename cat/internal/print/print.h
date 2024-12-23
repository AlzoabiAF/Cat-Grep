#ifndef PRINT_H_
#define PRINT_H_

#include <stddef.h>
#include <stdio.h>

#include "../../options.h"

bool isTab(char c);
bool isNewLine(char c);
bool isNoOptions(Options *flags);
bool isEmptyLine(FILE *file);

void print_char(unsigned char c, Options *options);
void printWithOptions(Options *options, char *filename);
void printWitoutOptions(char *filename);
void print(char *filename, Options *flags);

#endif