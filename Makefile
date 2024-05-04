CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

all:
	-gcc -c toml_parse.c utility.c game_frontend.c $(CFLAGS)
	-gcc game_frontend.o utility.o toml_parse.o -o game_frontend $(CFLAGS)
	-gcc main.c toml_parse.c -o main
	-gcc test.c toml_parse.c -o test

clean:
	rm -f test main game_frontend *.o