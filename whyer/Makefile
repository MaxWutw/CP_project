CFLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=gnu99 -Wall
LDFLAGS := `sdl2-config --libs` -lm -lSDL2_image -lSDL2_ttf

all: game

game: main.o game.o ui.o
	gcc main.o game.o ui.o -o game $(LDFLAGS)

main.o: main.c game.h ui.h
	gcc -c main.c $(CFLAGS)

game.o: game.c game.h
	gcc -c game.c $(CFLAGS)

ui.o: ui.c ui.h
	gcc -c ui.c $(CFLAGS)

clean:
	rm -f game *.o
