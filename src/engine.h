
#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "search.h"

#define ENGINE_ABORT 2

typedef struct {
  char *filename;
  search *search;
} engine;

engine *engine_new (void);
engine *engine_new2 (search *s, char *filename);
int engine_process_file(engine *self, char *f_ptr, off_t f_len);
int engine_run (engine *self);
void engine_destroy (engine *self);

#endif
