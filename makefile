CPP := g++
CPPFLAGS := -O3 -std=c++11 -Wall -Wextra
OBJ = obj
SRC = src
BUILD = build
TEST = test

all: $(BUILD)/browser

$(TEST)/tcp_stream_test: $(OBJ)/tcp_stream.o $(OBJ)/tcp_stream_test.o
	$(CPP) $(CPPFLAGS) -o $@ $^

$(OBJ)/tcp_stream.o: net/tcp_stream.h
	$(CPP) $(CPPFLAGS) -o $@ -c net/tcp_stream.cc

$(OBJ)/tcp_stream_test.o: net/tcp_stream_test.h
	$(CPP) $(CPPFLAGS) -o $@ -c net/tcp_stream_test.cc

.PHONY: clean all

clean:
	rm $(OBJ)/*.o $(BUILD)/* $(TEST)/*
