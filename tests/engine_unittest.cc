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
}
