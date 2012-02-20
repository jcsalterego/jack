#!/usr/bin/make

CC=gcc
CXX=g++

TESTS=\
	engine_unittest \
	options_unittest
TESTBIN_DIR=.

CPPFLAGS=-Wall -O3 -pg -g -I. -I../src
CPPFLAGS_EXTRA+=\
	-Waggregate-return \
	-Wcast-align \
	-Wcast-qual \
	-Wconversion \
	-Wextra \
	-Wfloat-equal \
	-Wno-unused-parameter \
	-Wpointer-arith \
	-Wshadow \
	-Wstrict-overflow=5 \
	-Wswitch-default \
	-Wswitch-enum \
	-Wundef \
	-Wwrite-strings
CXXFLAGS=$(CPPFLAGS)

GTEST_DIR=./googletest
CPPFLAGS += -I$(GTEST_DIR)/include
tests: $(TESTS)
	@./run_tests.sh

GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) \
	       -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) \
	       -c $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

%_unittest.o: %_unittest.cc %.h $(GTEST_HEADERS)
	$(CXX) $(CXXFLAGS) -c %_unittest.cc
%_unittest: %.o %_unittest.o gtest_main.a $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(TESTBIN_DIR)/$@

engine_unittest.o: engine_unittest.cc search.o engine.o $(GTEST_HEADERS)
	$(CXX) $(CXXFLAGS) -c engine_unittest.cc
engine_unittest: engine.o search.o engine_unittest.o gtest_main.a $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(TESTBIN_DIR)/$@

# options_unittest.o: options_unittest.cc options.o $(GTEST_HEADERS)
# 	$(CXX) $(CXXFLAGS) -c options_unittest.cc
# options_unittest: options.o options_unittest.o gtest_main.a $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(TESTBIN_DIR)/$@

%.o: ../src/%.c
	$(CC) -c $(CPPFLAGS_EXTRA) $+ -o $@
clean:
	rm -rf *_unittest *~ \#*\# *.o *.a gmon.out *.dSYM/
