
#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <stdlib.h>
#include <string.h>

typedef struct search {
  char *expr;
  char *key;
  char *value;
} search;

search *search_new (void);
search *search_new_from_expr (char *expr);
int search_run_on_file (char *filename);
void search_destroy (search *self);

#endif
