# CFLAGS := `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image 

# all:
# 	-gcc -c toml_parse.c utility.c game_frontend.c $(CFLAGS)
# 	-gcc game_frontend.o utility.o toml_parse.o -o game_frontend $(CFLAGS)
# 	-gcc main.c toml_parse.c -o main
# 	-gcc test.c toml_`parse.c -o test

# clean:
# 	rm -f test main game_frontend *.o


CFLAGS := `sdl2-config --cflags` -ggdb3 -O0 --std=gnu99 -Wall
LDFLAGS := `sdl2-config --libs` -lm -lSDL2_image -lSDL2_ttf -lSDL2_mixer

all: program

program: program.o utility.o toml_parse.o gameLoop.o freshNewScreen.o backpack.o \
constants.o musicUtil.o toml_parse_item.o player_stats.o userInput.o loadSaving.o utility.h \
gameLoop.h constants.h musicUtil.h toml_parse_item.h player_stats.h userInput.h loadSaving.h
	gcc -g program.o utility.o toml_parse.o gameLoop.o freshNewScreen.o \
	 backpack.o constants.o musicUtil.o toml_parse_item.o player_stats.o userInput.o \
	 loadSaving.o -o program $(LDFLAGS)

# main: main.o toml_parse.o
# 	gcc main.o toml_parse.o -o main $(LDFLAGS)

program.o: program.c
	gcc -c program.c $(CFLAGS)

gameLoop.o: gameLoop.c
	gcc -c gameLoop.c $(CFLAGS)

freshNewScreen.o: freshNewScreen.c
	gcc -c freshNewScreen.c $(CFLAGS)

main.o: main.c
	gcc -c main.c $(CFLAGS)

utility.o: utility.c
	gcc -c utility.c $(CFLAGS)

constants.o: constants.c constants.h
	gcc -c constants.c $(CFLAGS)

toml_parse.o: toml_parse.c toml_parse.h
	gcc -c toml_parse.c $(CFLAGS)

musicUtil.o: musicUtil.c musicUtil.h
	gcc -c musicUtil.c $(CFLAGS)

toml_parse_item.o: toml_parse_item.c toml_parse_item.h
	gcc -c toml_parse_item.c $(CFLAGS)

backpack.o: backpack.c backpack.h
	gcc -c backpack.c $(CFLAGS)

player_stats.o: player_stats.c player_stats.h
	gcc -c player_stats.c $(CFLAGS)

userInput.o: userInput.c userInput.h
	gcc -c userInput.c $(CFLAGS)

loadSaving.o: loadSaving.c loadSaving.h
	gcc -c loadSaving.c $(CFLAGS)

clean:
	rm -f test main game_frontend program *.o 

