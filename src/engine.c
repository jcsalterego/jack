
#include "engine.h"

engine *
engine_new (void)
{
  engine *self = (engine *)malloc(sizeof(engine));
  bzero(self, sizeof(engine));
  return self;
}

engine *
engine_new2 (search *s, char *filename)
{
  engine *self = engine_new();
  self->search = s;
  // copy filename
  size_t slen = strlen(filename);
  self->filename = (char *)malloc(sizeof(char)*(1+slen));
  memcpy(self->filename, filename, sizeof(char)*(0+slen));
  self->filename[slen] = '\0';
  return self;
}

/* print value (removes quotes) */
void
printv (char *p, char *pe)
{
  char text[1024];
  bzero(text, sizeof(char)*1024);
  if (*p == '"') {
    // assumes string ends correctly
    // doesn't bother escaping anything
    ++p;
    --pe;
  }
  size_t slen = (size_t)(pe - p);
  if (slen > 1024) {
    slen = 1024;
  }
  memcpy(text, p, sizeof(char) * slen);
  text[slen] = '\0';
  printf("%s\n", text);
}

/* print value raw */
void
printvr (char *p, char *pe)
{
  char text[1024];
  bzero(text, sizeof(char)*1024);
  size_t slen = (size_t)(pe - p);
  if (slen > 1024) {
    slen = 1024;
  }
  memcpy(text, p, sizeof(char) * slen);
  text[slen] = '\0';
  printf("%s\n", text);
}

void
engine_printv_last_match (engine *self)
{
  if (self && self->last_match && self->last_match_end) {
    self->json
      ? printvr(self->last_match, self->last_match_end)
      : printv(self->last_match, self->last_match_end);
  }
}

void
engine_extract_value_str (engine *self, char *p, char *ple)
{
  // find ending
  char *y = p;
  int done = 0;
  while (done == 0 && ++y < ple) {
    switch (*y) {
    case '\\':
      y += 2;
      break;
    case '"':
      ++y;
      done = 1;
      break;
    default:
      break;
    }
  }
  self->last_match = p;
  self->last_match_end = y;
  engine_printv_last_match(self);
}

void
engine_extract_value_null (engine *self, char *p, char *ple)
{
  // find ending
  if (p + 4 < ple && p[1] == 'u' && p[2] == 'l' && p[3] == 'l') {
    self->last_match = p;
    self->last_match_end = p + 4;
    engine_printv_last_match(self);
  }
}

void
engine_extract_value_num (engine *self, char *p, char *ple)
{
  // find ending
  char *y = p;
  int done = 0;
  while (done == 0 && ++y < ple) {
    switch (*y) {
    case '0': case '1': case '2': case '3': case '4': // fall-through
    case '5': case '6': case '7': case '8': case '9':
      break;
    default:
      done = 1;
      break;
    }
  }
  self->last_match = p;
  self->last_match_end = y;
  engine_printv_last_match(self);
}

void
engine_extract_value (engine *self, char *pneedle, char *ple)
{
  switch (pneedle[0]) {
  case '"':
    engine_extract_value_str(self, pneedle, ple);
    break;
  case '0': case '1': case '2': case '3': case '4': // fall-through
  case '5': case '6': case '7': case '8': case '9':
    engine_extract_value_num(self, pneedle, ple);
    break;
  case 'n':
    engine_extract_value_null(self, pneedle, ple);
    break;
  default:
    break;
  }
}

int
engine_process_line (engine *self, char *pl, char *ple)
{
  char needle[2048];

  if (self->debug) {
    char tmp[64];
    // silly debug info
    size_t slen = (size_t)(ple - pl);
    if (slen > 50) {
      slen = 50;
    }
    memcpy(tmp, pl, sizeof(char) * slen);
    tmp[slen] = '\0';
    fprintf(stderr, "*** line: '%s[...]'\n", tmp);
  }

  // compose search key
  size_t nlen = strlen(self->search->key);
  needle[0] = '"';
  memcpy(&needle[1], self->search->key, sizeof(char)*nlen);
  needle[nlen+1] = '"';
  needle[nlen+2] = ':';
  needle[nlen+3] = '\0';

  if (pl[0] != '{') {
    // not a hash
    return 0;
  } else {
    // keep track of all the first level braces
    // this WILL break with any braces in escaped strings.
    char *braces[NUM_BRACE_ITEMS];
    char *stack[STACK_DEPTH];
    int stack_pos = 0;
    int brace_pos = 0;
    bzero(stack, sizeof(char *) * STACK_DEPTH);
    char *cursor = NULL;
    for (cursor = pl; cursor < ple; ++cursor) {
      if (*cursor == '{') {
        // push
        if (stack_pos == 1) {
          // we've entered the 1st-level
          braces[brace_pos++] = cursor;
        }
        stack[stack_pos++] = cursor;
      } else if (*cursor == '}') {
        // pop
        stack[stack_pos--] = NULL;
        if (stack_pos == 1) {
          // we're back to the top-level
          // record closing brace
          braces[brace_pos++] = cursor;
        }
      }
    }
    // braces now has pairs of pointers of 1st level braces
    // e.g. "{{}{}}" => { 1, 2, 3, 4 }

    char *pneedle = NULL;
    int invalid = 0;
    while (pl < ple) {
      invalid = 0; // reset invalid flag
      // TODO: replace this with something less buffer-overflowy
      pneedle = strstr(pl, needle);
      if (!pneedle) {
        // nothing found at all means GTFO
        return 0;
      } else if (brace_pos > 0) {
        // if there are braces, compare pairs against found cursor
        int i;
        // can optimize starting brace_pos here.
        for (i = 0; i < brace_pos; i += 2) {
          if (braces[i] < pneedle && braces[i+1] > pneedle) {
            // you're within a level!
            // advance the starting pointer and retry
            pl = pneedle + 1;
            invalid = 1;
            break;
          }
        }
      }

      if (!invalid) {
        // if valid, go ahead and extract
        pneedle += strlen(needle);
        engine_extract_value(self, pneedle, ple);
        return 1;
      }
    }

    return 0;
  }
}

int
engine_process_file (engine *self, char *f_ptr, off_t f_len)
{
  if (self->search->key != NULL) {
    if (self->debug) {
      fprintf(stderr,
              "*** searching for key '%s' in '%s' of size %d\n",
              self->search->key, self->filename, (int)f_len);
    }

    // search for key in f_len
    char *f = f_ptr;
    char *fp = f_ptr + f_len;
    char *p = NULL;
    char *pl = NULL;
    char *ple = NULL;

    // emit lines
    for (p = pl = f; p < fp; p++) {
      if (*p == '\n') {
        ple = p; // reached EOL
        engine_process_line(self, pl, p);
        pl = p + 1;
      }
    }
    if (pl != p) {
      // one last line to process
      engine_process_line(self, pl, p);
    }
  } else {
    printf("searching for '%s' in '%s' of size %d\n",
           self->search->expr, self->filename, (int)f_len);
  }
  return 1;
}

int
engine_run (engine *self)
{
  int rv = 0;
  struct stat statbuf;
  char *f_ptr = NULL;
  int fd = -1;
  off_t f_len = 0;

  // open the file
  fd = open(self->filename, O_RDONLY);
  if (fd < 0) {
    fprintf(stderr, "oy, it failed!\n");
    return 0;
  }
  rv = fstat(fd, &statbuf);
  f_len = statbuf.st_size;

  f_ptr = mmap(0, (size_t)f_len, PROT_READ, MAP_SHARED, fd, (size_t)0);
  if (f_ptr == MAP_FAILED) {
    fprintf(stderr, "mmap failed\n");
    return 0;
  }

  // process here
  rv = engine_process_file(self, f_ptr, f_len);

  // cleanup
  if ((munmap(f_ptr, (size_t)f_len)) != 0) {
    fprintf(stderr, "munmap failed\n");
    return 0;
  }

  return rv;
}

void
engine_destroy (engine *self)
{
  if (self) {
    if (self->filename) {
      free(self->filename);
    }
    free(self);
  }
}
