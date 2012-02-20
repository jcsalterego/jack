
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
#define NUM_BRACE_ITEMS 2*NUM_BRACE_PAIRS
#define NUM_BRACE_PAIRS 10
#define STACK_DEPTH 16

typedef struct engine {
  char *filename;
  int debug;
  int json;
  struct search *search;
  char *last_match;
  char *last_match_end;
} engine;

engine *engine_new (void);
engine *engine_new2 (search *s, char *filename);
void engine_extract_value (engine *self, char *pneedle, char *ple);
void engine_extract_value_null (engine *self, char *p, char *ple);
void engine_extract_value_num (engine *self, char *p, char *ple);
void engine_extract_value_str (engine *self, char *p, char *ple);
void engine_printv_last_match (engine *self);
void engine_printvr_last_match (engine *self);
int engine_process_file (engine *self, char *f_ptr, off_t f_len);
int engine_process_line (engine *self, char *pl, char *ple);
int engine_run (engine *self);
void engine_destroy (engine *self);

void printv (char *p, char *pe);
void printvr (char *p, char *pe);

#endif
