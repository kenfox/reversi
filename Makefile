OBJS=game.o board.o sample.o
TESTS=game-test.cc board-test.cc #sample-test.cc

GTESTDIR=/Users/ken/proj/googletest/googletest
GMOCKDIR=/Users/ken/proj/googletest/googlemock
CXX=clang++
CXXFLAGS=-Wall -g -std=c++14
CXXTESTFLAGS=$(CXXFLAGS) -I$(GTESTDIR)/include -I$(GMOCKDIR)/include
LDFLAGS=-g

.PHONY: t clean

othello: main.o $(OBJS)
	$(CXX) -o $@ $(LDFLAGS) $^

main.o: main.cc game.h
game.o: game.cc game.h board.h
board.o: board.cc board.h
sample.o: sample.cc sample.h

t: $(OBJS) t.cc gtest.o gmock.o $(TESTS)
	$(CXX) -o $@ $(CXXTESTFLAGS) $^ && ./t

clean:
	rm -rf t othello *.o t.dSYM

gtest.o: $(GTESTDIR)/src/gtest-all.cc
	$(CXX) -c -o $@ $(CXXTESTFLAGS) -I$(GTESTDIR) $<

gmock.o: $(GMOCKDIR)/src/gmock-all.cc
	$(CXX) -c -o $@ $(CXXTESTFLAGS) -I$(GTESTDIR) -I$(GMOCKDIR) $<
