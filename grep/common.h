#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} Options;

#endif