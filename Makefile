CC = gcc
CFLAGS = -Wall -lSDL2 -lSDL2_image
EXEC = run

SRC = src/main/main.c src/graphics/graphics.c src/graphics/graphics.h src/gameobject/gameobject.c src/gameobject/gameobject.h

all:
	$(CC) $(SRC) $(CFLAGS) -o ./run/$(EXEC)
	
