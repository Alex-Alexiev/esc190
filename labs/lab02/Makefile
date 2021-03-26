CC := gcc
CC_FLAGS := -Wall 

BIN := bin
SRC := src
INCLUDE := include 

LIBRARIES := 
EXECUTABLE := main

all: $(BIN)/$(EXECUTABLE)

run: clean all 
	@./$(BIN)/$(EXECUTABLE)


$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CC) $(CC_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean: 
	-rm $(BIN)/*



.PHONY: test