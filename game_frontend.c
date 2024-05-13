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
#include <SDL_ttf.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#endif

int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    if(initializeSDL() == 0) return 0;
    // Basic setup start
    // get name
    const char *program_name = NULL;
    if((program_name = get_name(pFile)) == NULL){
        fprintf(stderr, "Error: Failed to get the name from get_name function! Program Terminated!!\n");
        return 0;
    }
    printf("%s\n", program_name);

    // window
    SDL_Window *win = NULL;
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM.w, DM.h, SDL_WINDOW_RESIZABLE);
    printf("window width: %d \nwindow height: %d\n", DM.w, DM.h);
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
    if(surface == NULL){
        fprintf(stderr, "Error: Surface could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(win);
        return 0;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);

    // Font
    TTF_Font* font = TTF_OpenFont("font_lib/Martyric_PersonalUse.ttf", 24);
    if (font == NULL) {
        SDL_Log("Error: Failed to load font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
        SDL_DestroyTexture(tex);
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(win);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Color color = {255, 255, 255};


    // Button setup
    const int32_t start_button_width = 350, start_button_height = 100;
    const int32_t start_button_x = (DM.w - start_button_width) / 2, start_button_y = (DM.h - start_button_height);
    SDL_Rect buttonRect = {start_button_x, start_button_y, start_button_width, start_button_height};
    // printf("%d %d %d %d\n", start_button_height, start_button_width, start_button_x, start_button_y);

    int8_t quit = 0;
    while(!quit){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = 1;
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                int32_t mousex, mousey;
                SDL_GetMouseState(&mousex, &mousey);
                if(SDL_PointInRect(&(SDL_Point){mousex, mousey}, &buttonRect)){
                    printf("Button Clicked\n");
                }
            }
        }

        SDL_Rect dstrect = {270, 0, 900, 900};
        // clears the screen
        SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
        SDL_RenderClear(render);

        // Render the window
        SDL_RenderCopy(render, tex, NULL, &dstrect);
        SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
        SDL_RenderFillRect(render, &buttonRect);

        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(render);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
    // Basic setup end


    // close ttf
    TTF_CloseFont(font);

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(render);

    // destory window
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include "toml_parse.h"
// #include "utility.h"
// #ifdef __linux__
// #include <SDL2/SDL.h> 
// #include <SDL2/SDL_image.h> 
// #include <SDL2/SDL_timer.h>
// #include <SDL_ttf.h>
// #elif __APPLE__
// #include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_timer.h>
// #include <SDL_ttf.h>
// #endif


// #define SCREEN_WIDTH 640
// #define SCREEN_HEIGHT 480
// #define MENU_ITEM_HEIGHT 50
// #define MENU_ITEM_PADDING 10

// // 選單項目的數量
// #define MENU_ITEM_COUNT 3

// // 選單項目的文字
// const char* menu_items[MENU_ITEM_COUNT] = {
//     "Option 1",
//     "Option 2",
//     "Option 3"
// };

// int selected_item = 0;

// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
// SDL_Surface* surface = NULL;
// SDL_Texture* texture = NULL;
// TTF_Font* font = NULL;

// bool _initializeSDL() {
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }

//     window = SDL_CreateWindow("Menu Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//     if (window == NULL) {
//         printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }

//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//     if (renderer == NULL) {
//         printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
//         return false;
//     }

//     return true;
// }

// bool loadFont() {
//     if (TTF_Init() < 0) {
//         printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
//         return false;
//     }

//     font = TTF_OpenFont("font_lib/Arial.ttf", 28);
//     if (font == NULL) {
//         printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
//         return false;
//     }

//     return true;
// }

// void renderMenu() {
//     SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//     SDL_RenderClear(renderer);

//     for (int i = 0; i < MENU_ITEM_COUNT; ++i) {
//         SDL_Rect itemRect = {0, i * (MENU_ITEM_HEIGHT + MENU_ITEM_PADDING), SCREEN_WIDTH, MENU_ITEM_HEIGHT};
//         SDL_Color textColor = {0, 0, 0};

//         if (i == selected_item) {
//             textColor.r = 255;
//         }

//         surface = TTF_RenderText_Blended(font, menu_items[i], textColor);
//         texture = SDL_CreateTextureFromSurface(renderer, surface);
//         SDL_FreeSurface(surface);

//         SDL_RenderCopy(renderer, texture, NULL, &itemRect);
//         SDL_DestroyTexture(texture);
//     }

//     SDL_RenderPresent(renderer);
// }

// void handleInput() {
//     SDL_Event e;

//     while (SDL_PollEvent(&e) != 0) {
//         if (e.type == SDL_QUIT) {
//             SDL_Quit();
//             exit(0);
//         } else if (e.type == SDL_KEYDOWN) {
//             switch (e.key.keysym.sym) {
//                 case SDLK_UP:
//                     selected_item = (selected_item - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
//                     break;
//                 case SDLK_DOWN:
//                     selected_item = (selected_item + 1) % MENU_ITEM_COUNT;
//                     break;
//                 case SDLK_RETURN:
//                     printf("Selected item: %s\n", menu_items[selected_item]);
//                     break;
//             }
//         }
//     }
// }

// int main(int argc, char* args[]) {
//     if (!_initializeSDL()) {
//         return 1;
//     }

//     if (!loadFont()) {
//         return 1;
//     }

//     bool quit = false;

//     while (!quit) {
//         handleInput();
//         renderMenu();
//     }

//     return 0;
// }
