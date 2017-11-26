CXXFLAGS=-std=c++17 -Wall -Wextra -pedantic
OBJS=base-element.o binary.o binstring.o codew.o document.o parser.o

PATHOBJS=$(addprefix src/, $(OBJS))

BIN=src/bson-parser

$(BIN): $(PATHOBJS)

debug: CXXFLAGS += -O0 -g3 -fno-inline
debug: $(BIN)

clean:
	$(RM) $(PATHOBJS)
	$(RM) $(BIN)

.PHONY: clean debug
