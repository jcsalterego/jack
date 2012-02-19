
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
  options *opts = options_from_args(argc, argv);
  if (opts->error) {
    usage();
    return EXIT_FAILURE;
  } else if (opts->version) {
    printf("jack version " APP_VERSION_STR "\n");
  } else {
    if (opts->needle) {
      // do your search here
    }
  }
  return EXIT_SUCCESS;
}
