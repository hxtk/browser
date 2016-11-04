# Copyright: Peter Sanders. All rights reserved.
# Date: 2016-11-03

OBJ = obj
SRC = src
BUILD = build
TEST = test

CPP := g++
CPPFLAGS := -O3 -std=c++11 -Wall -Wextra -I$(SRC)

all: $(BUILD)/browser

test: $(TEST)/tcp_stream_test

$(OBJ)/%.o: %(SRC)/%.h

$(TEST)/tcp_stream_test: $(OBJ)/tcp_stream.o $(OBJ)/tcp_stream_test.o
	$(CPP) $(CPPFLAGS) -o $@ $^

$(OBJ)/tcp_stream.o: $(SRC)/net/tcp_stream.h
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/net/tcp_stream.cc

$(OBJ)/tcp_stream_test.o: $(SRC)/net/tcp_stream_test.cc
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/net/tcp_stream_test.cc

.PHONY: clean all test

clean:
	rm $(OBJ)/*.o $(BUILD)/* $(TEST)/*
