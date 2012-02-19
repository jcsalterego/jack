
#include "search.h"

search *
search_new (void)
{
  search *self = (search *)malloc(sizeof(search));
  bzero(self, sizeof(search));
  return self;
}

search *
search_new_from_expr (char *expr)
{
  search *self = search_new();
  size_t slen = strlen(expr);
  self->expr = (char *)malloc(sizeof(char)*(1+slen));
  memcpy(self->expr, expr, sizeof(char)*(0+slen));
  self->expr[slen] = '\0';

  // detect whether this is a key search
  if (slen > 1 && self->expr[slen-1] == ':') {
    // expr ends in colon, so this is a key search
    self->key = (char *)malloc(sizeof(char)*(slen));
    memcpy(self->key, expr, sizeof(char)*(slen-1));
    self->key[slen-1] = '\0';
  }

  return self;
}

int
search_run_on_file (char *filename)
{
  return 1;
}

void
search_destroy (search *self)
{
  if (self) {
    if (self->expr) {
      free(self->expr);
    }
    if (self->key) {
      free(self->key);
    }
    free(self);
  }
}
