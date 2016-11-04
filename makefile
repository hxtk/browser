# Copyright: Peter Sanders. All rights reserved.
# Date: 2016-11-03

OBJ = obj
SRC = src
BUILD = build
TEST = test

CPP := g++
CPPFLAGS := -O3 -std=c++11 -Wall -Wextra -I$(SRC)

### General rules
all: $(BUILD)/browser

test: $(TEST)/tcp_stream_test

clean:
	rm $(OBJ)/*.o $(BUILD)/* $(TEST)/*

$(OBJ)/%.o: %(SRC)/%.h

### Unit tests
$(TEST)/tcp_stream_test: $(OBJ)/tcp_stream.o $(OBJ)/tcp_stream_test.o
	$(CPP) $(CPPFLAGS) -o $@ $^

### net objects
$(OBJ)/tcp_stream.o: $(SRC)/net/tcp_stream.h
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/net/tcp_stream.cc

$(OBJ)/tcp_stream_test.o: $(SRC)/net/tcp_stream_test.cc
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/net/tcp_stream_test.cc

### dom objects
$(OBJ)/node.o: $(SRC)/dom/node.h
	$(CPP) $(CPPFLAGS) -o $@ -c $^

$(OBJ)/document.o: $(SRC)/dom/document.h $(SRC)/dom/node.h
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/dom/document.h

$(OBJ)/element.o: $(SRC)/dom/element.h $(SRC)/dom/node.h
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/dom/element.h

$(OBJ)/text.o: $(SRC)/dom/text.h $(SRC)/dom/node.h
	$(CPP) $(CPPFLAGS) -o $@ -c $(SRC)/dom/text.h

.PHONY: clean all test

