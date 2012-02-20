
#include "jack.h"

void
usage (void)
{
  printf(
    "Usage: jack [OPTION]... PATTERN [FILE] ...\n"
    "Search for PATTERN in JSON files.\n\n"
    "General options:\n"
    "  -d\tdebug mode\n"
    "  -j\toutput raw json (quoted strings)\n"
    "  -V\tprint version information and exit\n"
  );
}

int
main (int argc, char **argv)
{
  int i, rv = 0;
  search *s = NULL;
  options *opts = options_from_args(argc, argv);
  if (opts->error) {
    usage();
    return EXIT_FAILURE;
  } else if (opts->version) {
    printf("jack version " APP_VERSION_STR "\n");
  } else if (opts->needle) {
    s = search_new_from_expr(opts->needle);
    fprintf(stderr, "*** searching for '%s'\n", s->expr);
    for (i = 0; i < opts->num_haystacks; i++) {
      fprintf(stderr, "*** target file = %s\n", opts->haystacks[i]);
      engine *e = engine_new2(s, opts->haystacks[i]);
      e->json = opts->json;
      rv = engine_run(e);
    }
    search_destroy(s);
  }
  options_destroy(opts);
  if (rv != 1) {
    fprintf(stderr, "non-success code: %d\n", rv);
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
}
