
#include "options.h"

options *
options_new (void)
{
  options *c = malloc(sizeof(options));
  bzero(c, sizeof(options));
  return c;
}

void
options_destroy (options *self)
{
  if (self) {
    free(self);
  }
}

options *
options_from_args (int argc, char **argv)
{
  options *c = malloc(sizeof(options));
  bzero(c,sizeof(options));

  int ch;
  while ((ch = getopt(argc, argv, "v")) != -1) {
    switch (ch) {
    case 'v':
      c->version = 1;
      break;
    default:
      c->error = 1;
      break;
    }
  }

  return c;
}
