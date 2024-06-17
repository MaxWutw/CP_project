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
SRC_DIR := src
OBJ_DIR := obj
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(wildcard $(SRC_DIR)/*.h)

all: engine

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

engine: $(OBJ_DIR) $(OBJS)
	gcc $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -rf engine $(OBJ_DIR)

.PHONY: clean all