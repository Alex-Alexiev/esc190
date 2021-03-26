CC := gcc
CC_FLAGS := -Wall -g

EXECUTABLE := main

all: $(EXECUTABLE)

run: clean all 
	clear 
	@./$(EXECUTABLE)

$(EXECUTABLE): *.c
	$(CC) $(CC_FLAGS) $^ -o $@ 

clean: 
	-rm $(EXECUTABLE)

.PHONY: test