CC=gcc
CFLAGS=-Wall -lm 
OBJ=obj
BIN=bin

all: 
	$(MAKE) -C Maths/ 
	$(MAKE) -C Models/
	$(CC) main.c -o $(BIN)/main $(OBJ)/*.o $(CFLAGS)

clean: 
	rm -rf $(BIN)/ $(OBJ)
	mkdir $(BIN)/ $(OBJ)
