SOURCES := $(wildcard *.c)
EXECUTABLES := $(SOURCES:.c=)
CFLAGS := -Wall -Werror -g
# CFLAGS += `sdl2-config --libs --cflags` -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
OBJ=main.o test.o toml_parse
all: $(EXECUTABLES)



%: %.o $(OBJ)
	-gcc $^ -o $@

main.o: main.c toml_parse.h
test.o: test.c toml_parse.h
toml_parse.o: toml_parse.c toml_parse.h

.PHONY: clean
clean:
	rm -f $(EXECUTABLES) *.o