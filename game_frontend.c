#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "toml_parse.h"
#include "utility.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#endif

// // 定義按鈕的位置和大小
// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define BUTTON_WIDTH 200
// #define BUTTON_HEIGHT 100
// #define BUTTON_X (SCREEN_WIDTH - BUTTON_WIDTH) / 2
// #define BUTTON_Y (SCREEN_HEIGHT - BUTTON_HEIGHT) / 2

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    if(initializeSDL() == -1) return 0;
    // Basic setup start
    // get name
    const char *program_name = NULL;
    if((program_name = get_name(pFile)) == NULL){
        fprintf(stderr, "Error: Failed to get the name from get_name function! Program Terminated!!\n");
        return 0;
    }

    // window
    SDL_Window *win = NULL;
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM.w, DM.h, SDL_WINDOW_RESIZABLE);
    printf("window width: %d \n window height: %d\n", DM.w, DM.h);
    SDL_ShowWindow(win);
    if(win == NULL){
        fprintf(stderr, "Error: Window could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    // Renderer
    SDL_Renderer *render = NULL;
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(render == NULL){
        fprintf(stderr, "Error: Renderer could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        return 0;
    }
    
    // Surface
    SDL_Surface *surface;
    surface = IMG_Load("img/cover.jpg");

    SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);

    // Button setup
    // SDL_Rect buttonRect = {BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT};

    int8_t quit = 0;
    while(!quit){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = 1;
                break;
            }
            // else if(event.type == SDL_MOUSEBUTTONDOWN){
            //     int32_t mousex, mousey;
            //     SDL_GetMouseState(&mousex, &mousey);
            //     if(SDL_PointInRect(&(SDL_Point){mousex, mousey}, &buttonRect)){
            //         printf("Button Clicked\n");
            //     }
            // }
        }

        SDL_Rect dstrect = {270, 0, 900, 900};
        // clears the screen
        SDL_RenderClear(render);

        // Render the window
        SDL_RenderCopy(render, tex, NULL, &dstrect);
        // SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
        // SDL_RenderFillRect(render, &buttonRect);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
    // Basic setup end


    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(render);

    // destory window
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}