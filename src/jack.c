
#include "jack.h"

void
usage (void)
{
  printf(
    "Usage: jack [OPTION]... PATTERN [FILE] ...\n\n"
    "Search for PATTERN in JSON files.\n"
  );
}

int
main (int argc, char **argv)
{
  options *c = options_from_args(argc, argv);
  if (c->error) {
    usage();
    return EXIT_FAILURE;
  } else if (c->version) {
    printf("jack version " APP_VERSION_STR "\n");
  }
  return EXIT_SUCCESS;
}
