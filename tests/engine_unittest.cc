/**
 * Engine Unit Tests
 */

extern "C" {
#include "search.h"
#include "engine.h"
}
#include "gtest/gtest.h"

class EngineTestSuite : public testing::Test
{
 public:
  virtual void SetUp() {
    e = engine_new();
  }
  virtual void TearDown() {
    engine_destroy(e);
  }

  engine *e;
};

TEST_F(EngineTestSuite, engine_new2) {
  char filename[] = "filename";
  search *s = search_new();
  engine *e = engine_new2(s, filename);
  ASSERT_EQ(0, strcmp(filename, e->filename));
  ASSERT_EQ(s, e->search);

  search_destroy(s);
  engine_destroy(e);
}

TEST_F(EngineTestSuite, engine_process_line_simple) {
  char haystack[] = "{\"foo\":\"bar\"}";
  char *p = haystack;
  char *pe = &haystack[strlen(haystack)];

  search *s = search_new_from_expr((char *)"foo:");
  engine *e = engine_new2(s, (char *)"");
  int rv = engine_process_line(e, p, pe);

  ASSERT_EQ(0, strncmp("\"bar\"", e->last_match,
                       e->last_match_end - e->last_match));
  ASSERT_EQ(1, rv);

  search_destroy(s);
  engine_destroy(e);
}

TEST_F(EngineTestSuite, engine_process_line_exact_match) {
  char haystack[] = "{\"wufoo\":\"bar\",\"foo\":\"baz\"}";
  char *p = haystack;
  char *pe = &haystack[strlen(haystack)];

  search *s = search_new_from_expr((char *)"foo:");
  engine *e = engine_new2(s, (char *)"");
  int rv = engine_process_line(e, p, pe);

  ASSERT_EQ(0, strncmp("\"baz\"", e->last_match,
                       e->last_match_end - e->last_match));
  ASSERT_EQ(1, rv);

  search_destroy(s);
  engine_destroy(e);
}

TEST_F(EngineTestSuite, engine_process_line_correct_level) {
  char haystack[] = "{\"foo\":{\"bar\":\"baz\"},\"bar\":\"qux\"}";
  char *p = haystack;
  char *pe = &haystack[strlen(haystack)];

  search *s = search_new_from_expr((char *)"bar:");
  engine *e = engine_new2(s, (char *)"");
  int rv = engine_process_line(e, p, pe);

  ASSERT_EQ(0, strncmp("\"qux\"", e->last_match,
                       e->last_match_end - e->last_match));
  ASSERT_EQ(1, rv);

  search_destroy(s);
  engine_destroy(e);
}


TEST_F(EngineTestSuite, engine_process_line_correct_even_with_multi_levels) {
  char haystack[] = "{\"foo\":{\"bar\":{\"haha\":\"baz\"}},\"bar\":\"qux\"}";
  char *p = haystack;
  char *pe = &haystack[strlen(haystack)];

  search *s = search_new_from_expr((char *)"bar:");
  engine *e = engine_new2(s, (char *)"");
  int rv = engine_process_line(e, p, pe);

  ASSERT_EQ(0, strncmp("\"qux\"", e->last_match,
                       e->last_match_end - e->last_match));
  ASSERT_EQ(1, rv);

  search_destroy(s);
  engine_destroy(e);
}
