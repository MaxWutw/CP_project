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
#include <SDL2/SDL_ttf.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#endif

int8_t game_is_running = 1;
int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    // atexit(DestoryAll);
    if( (game_is_running = initializeSDL()) == 0){
        fprintf(stderr, "Error: Failed to initialize SDL! Program Termainated!!\nSDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // get name
    const char *program_name = NULL;
    if((program_name = get_name(pFile)) == NULL){
        fprintf(stderr, "Error: Failed to get the name from get_name function! Program Terminated!!\n");
        return 0;
    }
    printf("%s\n", program_name);
    // setup
    SDL_Window *win = NULL;
    SDL_DisplayMode DM;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;
    TTF_Font *TitleFont = NULL;
    setup(program_name, win, renderer, surface, texture, TitleFont, &DM);
    // texture = SDL_CreateTextureFromSurface(renderer, surface);
    // SDL_FreeSurface(surface);

    while(game_is_running){
        game_is_running = process_input();
        // update();
        // render();
    }
    // close ttf
    TTF_CloseFont(TitleFont);

    // destroy texture
    SDL_DestroyTexture(texture);

    // destroy renderer
    SDL_DestroyRenderer(renderer);

    // destory window
    SDL_DestroyWindow(win);

    SDL_Quit();
    // DestoryAll_and_Quit(TitleFont, texture, renderer, win);

    return 0;
}