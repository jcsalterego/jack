
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define MAX_HAYSTACKS 10

typedef struct options {
  int version;
  int error;
  int debug;
  int help;
  int json;
  char *needle;
  char *haystacks[MAX_HAYSTACKS];
  int num_haystacks;
} options;

options *options_new (void);
void options_destroy (options *self);
options *options_from_args (int argc, char **argv);

#endif
