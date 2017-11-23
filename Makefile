CC=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra -pedantic
OBJS=base-element.o binary.o binstring.o codew.o document.o parser.o

PATHOBJS=$(addprefix src/, $(OBJS))

BIN=bson

$(BIN): $(PATHOBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(PATHOBJS)
	$(RM) $(BIN)

.PHONY: clean
