CC = gcc
CFLAGS = -Wall -lSDL2 -lSDL2_image
EXEC = run

SRC = src/main/main.c src/graphics/graphics.c src/graphics/graphics.h src/gameobject/gameobject.c src/gameobject/gameobject.h

all: linux windows

linux:
	$(CC) $(SRC) $(CFLAGS) -o ./run/$(EXEC)Linux

windows:
	$(CC) $(SRC) $(CFLAGS) -o ./run/$(EXEC)Windows.exe

