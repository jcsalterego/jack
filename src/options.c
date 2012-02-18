
#include "options.h"

options *
options_new (void)
{
  options *self = malloc(sizeof(options));
  bzero(self, sizeof(options));
  return self;
}

void
options_destroy (options *self)
{
  if (self) {
    if (self->needle) {
      free(self->needle);
    }
    free(self);
  }
}

options *
options_from_args (int argc, char **argv)
{
  options *self = options_new();

  int ch;
  while ((ch = getopt(argc, argv, "v")) != -1) {
    switch (ch) {
    case 'v':
      self->version = 1;
      break;
    default:
      self->error = 1;
      break;
    }
  }

  argc -= optind;
  argv += optind;

  if (argc > 0) {
    size_t slen = strlen(argv[0]);
    self->needle = (char *)malloc(sizeof(char)*(1+slen));
    memcpy(self->needle, argv[0], sizeof(char)*(0+slen));
    self->needle[slen] = '\0';

    --argc;
    ++argv;
  }

  return self;
}
