#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml_parse.h"
#include "utility.h"
#include "constants.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#endif
int8_t game_is_running = 1;
int main(int argc, char *argv[]){
    atexit(DestoryAll);
    game_is_running = initializeSDL();

    while(game_is_running){
        process_input();
        update();
        render();
    }


    return 0;
}