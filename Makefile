OBJS=board.o sample.o
TESTS=board-test.cc #sample-test.cc

GTESTDIR=/Users/ken/proj/googletest/googletest
CXX=clang++
CXXFLAGS=-g -std=c++14
CXXTESTFLAGS=$(CXXFLAGS) -I$(GTESTDIR)/include
LDFLAGS=-g

.PHONY: t clean

othello: main.o $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^

sample.o: sample.cc sample.h

t: $(OBJS) t.cc gtest.o $(TESTS)
	$(CXX) -o $@ $(CXXTESTFLAGS) $^ && ./t

clean:
	rm -rf t othello *.o t.dSYM

gtest.o: $(GTESTDIR)/src/gtest-all.cc
	$(CXX) -c -o $@ $(CXXTESTFLAGS) -I$(GTESTDIR) $<
