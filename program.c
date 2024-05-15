#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "toml_parse.h"
#include "utility.h"
#include "constants.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <SDL_ttf.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#endif

int8_t title_is_running = 1;
int8_t selected_item = 0;
int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    // atexit(DestoryAll);
    if( (title_is_running = initializeSDL()) == 0){
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
    setup(program_name, &win, &renderer, &DM);
    uint32_t last_frame_time = 0.0;
    SDL_Rect textRect;
    SDL_Color color_white = {255, 255, 255};
    // SDL_Color color_black = {0, 0, 0};
    const char *TitleText = "Life Simulator";
    textRect.w = 500;
    textRect.h = 200;
    textRect.x = ((DM.w - textRect.w) / 2);
    textRect.y = ((DM.h - textRect.h) / 2) - 250;
    int32_t inc = 1, base_y = textRect.y;
    // const char* menu_items[MENU_ITEM_COUNT] = {
    //     "Start",
    //     "Story",
    //     "Author"
    // };
    int32_t title_status = 0;
    while(title_is_running){
        update_title_screen(&last_frame_time, &textRect, &inc, &base_y);
        // render_title_screen(&win, &renderer, &DM, &textRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", TitleText, textRect.x, textRect.y, textRect.w, textRect.h, 108, &color_white);
        SDL_Rect fillRect1 = {(DM.w - 200) / 2, (DM.h - 50) / 2, 200, 100};
        SDL_Rect fillRect2 = {(DM.w - 200) / 2, (DM.h + 200) / 2, 200, 100};
        SDL_Rect fillRect3 = {(DM.w - 200) / 2, (DM.h + 450) / 2, 200, 100};

        title_is_running = process_input(&selected_item, &fillRect1, &fillRect2, &fillRect3, renderer, &title_status);
        // draw option
        // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        // SDL_RenderFillRect(renderer, &fillRect1);
        // rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "Start Game", (DM.w - 200) / 2, (DM.h - 50) / 2, 200, 100, 48, &color_black);
        // // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        // SDL_RenderFillRect(renderer, &fillRect2);
        // rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "How To Play", (DM.w - 200) / 2, (DM.h + 200) / 2, 200, 100, 40, &color_black);
        // // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        // SDL_RenderFillRect(renderer, &fillRect3);
        // rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "Author", (DM.w - 200) / 2, (DM.h + 450) / 2, 200, 100, 48, &color_black);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
    // close ttf
    // TTF_CloseFont(TitleFont);

    // destroy texture
    // SDL_DestroyTexture(texture);

    // destroy renderer
    SDL_DestroyRenderer(renderer);

    // destory window
    SDL_DestroyWindow(win);

    SDL_Quit();
    // DestoryAll_and_Quit(TitleFont, texture, renderer, win);

    return 0;
}