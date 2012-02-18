
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

typedef struct {
  int version;
  int error;
  char *needle;
} options;

options *options_new (void);
void options_destroy (options *self);
options *options_from_args (int argc, char **argv);

#endif
