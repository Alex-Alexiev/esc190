CC := gcc
CC_FLAGS := -g

BIN := bin
SRC := 

INCLUDE := 

LIBRARIES := 
EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: all 
	@./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): *.c
	$(CC) $(CC_FLAGS) $(INCLUDE) $^ -o $@ $(LIBRARIES)

.PHONY: test