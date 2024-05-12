# CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image 

# all:
# 	-gcc -c toml_parse.c utility.c game_frontend.c $(CFLAGS)
# 	-gcc game_frontend.o utility.o toml_parse.o -o game_frontend $(CFLAGS)
# 	-gcc main.c toml_parse.c -o main
# 	-gcc test.c toml_parse.c -o test

# clean:
# 	rm -f test main game_frontend *.o


CFLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=gnu99 -Wall
LDFLAGS := `sdl2-config --libs` -lm -lSDL2_image -lSDL2_ttf

all: game_frontend main test program

program: program.o utility.o toml_parse.o utility.h
	gcc program.o utility.o toml_parse.o -o program $(LDFLAGS)

game_frontend: game_frontend.o utility.o toml_parse.o utility.h
	gcc game_frontend.o utility.o toml_parse.o -o game_frontend $(LDFLAGS)

main: main.o toml_parse.o
	gcc main.o toml_parse.o -o main $(LDFLAGS)

test: test.o toml_parse.o
	gcc test.o toml_parse.o -o test $(LDFLAGS)

program.o: program.c
	gcc -c program.c $(CFLAGS)

game_frontend.o: game_frontend.c
	gcc -c game_frontend.c $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

test.o: test.c
	gcc -c test.c $(CFLAGS)

utility.o: utility.c
	gcc -c utility.c $(CFLAGS)

toml_parse.o: toml_parse.c
	gcc -c toml_parse.c $(CFLAGS)

clean:
	rm -f test main game_frontend program *.o 

