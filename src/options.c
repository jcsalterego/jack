
#include "options.h"

options *
options_new (void)
{
  options *self = malloc(sizeof(options));
  bzero(self, sizeof(options));
  self->num_haystacks = 0;
  return self;
}

void
options_destroy (options *self)
{
  int i;
  if (self) {
    if (self->needle) {
      free(self->needle);
    }
    for (i = 0; i < MAX_HAYSTACKS; i++) {
      if (self->haystacks[i]) {
        free(self->haystacks[i]);
      }
    }
    free(self);
  }
}

options *
options_from_args (int argc, char **argv)
{
  int i;
  options *self = options_new();

  int ch;
  while ((ch = getopt(argc, argv, "v")) != -1) {
    switch (ch) {
    case 'd':
      self->debug = 1;
      break;
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

  for (i = 0; i < MAX_HAYSTACKS && i < argc; i++) {
    // populate haystacks
    size_t slen = strlen(argv[i]);
    self->haystacks[i] = (char *)malloc(sizeof(char)*(1+slen));
    memcpy(self->haystacks[i], argv[i], sizeof(char)*(0+slen));
    self->haystacks[i][slen] = '\0';
    self->num_haystacks++;
  }

  return self;
}
