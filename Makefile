SOURCES := $(wildcard *.c)
EXECUTABLES := $(SOURCES:.c=)
CFLAGS := -Wall -Werror -g -O0 --std=c99
# CFLAGS += `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lSDL2_ttf -lm
CFLAGS+=`sdl2-config --cflags`
LFLAGS=`sdl2-config --libs` -lSDL2_ttf

OBJ=main.o test.o toml_parse
all: $(EXECUTABLES)

%: %.o
	# -gcc $^ -o $@
	-gcc main.o toml_parse.o -o main
	-gcc test.o toml_parse.o -o test
	-gcc $(CFLAGS) game_frontend.o utility.o toml_parse.o -o game_frontend

main.o: main.c toml_parse.h
test.o: test.c toml_parse.h
toml_parse.o: toml_parse.c toml_parse.h
utility.o: utility.c utility.h

.PHONY: clean
clean:
	rm -f $(EXECUTABLES) *.o