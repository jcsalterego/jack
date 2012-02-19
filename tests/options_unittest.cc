/**
 * Options Unit Tests
 */

#include "options.h"
#include "gtest/gtest.h"

class OptionsTestSuite : public testing::Test
{
 public:
  virtual void SetUp() {
    opts = options_new();
  }
  virtual void TearDown() {
    options_destroy(opts);
  }

  options *opts;
};

TEST_F(OptionsTestSuite, options_new_zero_haystacks) {
  ASSERT_EQ(0, opts->num_haystacks);
}

TEST_F(OptionsTestSuite, options_from_args_d_is_debug) {
  char *argv[] = {(char *)"jack", (char *)"-d"};
  options *opts = options_from_args(2, argv);
  ASSERT_EQ(1, opts->debug);
  options_destroy(opts);
}

TEST_F(OptionsTestSuite, options_from_args_V_is_version) {
  char *argv[] = {(char *)"jack", (char *)"-V"};
  options *opts = options_from_args(2, argv);
  ASSERT_EQ(1, opts->version);
  options_destroy(opts);
}

TEST_F(OptionsTestSuite, options_from_args_unknown_flag_causes_errors) {
  char *argv[] = {(char *)"jack", (char *)"-@"};
  options *opts = options_from_args(2, argv);
  ASSERT_EQ(1, opts->error);
  options_destroy(opts);
}
