/**
 * Options Unit Tests
 */

extern "C" {
#include "options.h"
}
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

TEST_F(OptionsTestSuite, options_from_args_needle_and_haystacks) {
  char *argv[] = {
    (char *)"jack", (char *)"needle",
    (char *)"haystack1", (char *)"haystack2", (char *)"haystack3"
  };
  options *opts = options_from_args(5, argv);
  ASSERT_STREQ(argv[1], opts->needle);
  ASSERT_STREQ(argv[2], opts->haystacks[0]);
  ASSERT_STREQ(argv[3], opts->haystacks[1]);
  ASSERT_STREQ(argv[4], opts->haystacks[2]);
  ASSERT_EQ(NULL, opts->haystacks[3]);
  options_destroy(opts);
}

TEST_F(OptionsTestSuite, options_from_args_needle) {
  char *argv[] = {(char *)"jack", (char *)"needle"};
  options *opts = options_from_args(2, argv);
  ASSERT_STREQ(argv[1], opts->needle);
  options_destroy(opts);
}
