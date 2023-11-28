CC=gcc
OBJ=obj
BIN=bin

CFLAGS=-Wall `sdl2-config --cflags --libs` -lm -lSDL2_image -lSDL2_ttf

all: 
	$(MAKE) -C ../CMaths/ 
	$(MAKE) -C Models/
	$(CC) main.c -o $(BIN)/main $(OBJ)/*.o ../SEngine/obj/*.o ../CMaths/obj/*.o $(CFLAGS)

clean: 
	rm -rf $(BIN)/ $(OBJ)
	mkdir $(BIN)/ $(OBJ)
