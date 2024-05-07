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
// #elif __APPLE__
// #include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_timer.h>
// #endif

// int main(int argc, char *argv[]){
//     FILE *pFile = NULL;
//     if(((pFile = fopen("script.toml", "r")) == NULL)){
//         fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
//         return 0;
//     }
//     if(initializeSDL() == -1) return 0;
//     // Basic setup start
//     // get name
//     const char *program_name = NULL;
//     if((program_name = get_name(pFile)) == NULL){
//         fprintf(stderr, "Error: Failed to get the name from get_name function! Program Terminated!!\n");
//         return 0;
//     }

//     // window
//     SDL_Window *win = NULL;
//     SDL_DisplayMode DM;
//     SDL_GetCurrentDisplayMode(0, &DM);
//     win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM.w, DM.h, SDL_WINDOW_RESIZABLE);
//     printf("window width: %d \nwindow height: %d\n", DM.w, DM.h);
//     SDL_ShowWindow(win);
//     if(win == NULL){
//         fprintf(stderr, "Error: Window could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
//         return 0;
//     }
//     // Renderer
//     SDL_Renderer *render = NULL;
//     render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//     if(render == NULL){
//         fprintf(stderr, "Error: Renderer could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
//         SDL_DestroyWindow(win);
//         return 0;
//     }
    
//     // Surface
//     SDL_Surface *surface;
//     surface = IMG_Load("img/cover.jpg");
//     if(surface == NULL){
//         fprintf(stderr, "Error: Surface could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
//         SDL_DestroyRenderer(render);
//         SDL_DestroyWindow(win);
//         return 0;
//     }

//     SDL_Texture *tex = SDL_CreateTextureFromSurface(render, surface);
//     SDL_FreeSurface(surface);

//     // Font
//     TTF_Font* font = TTF_OpenFont("lib/arial.ttf", 24);
//     if (font == NULL) {
//         SDL_Log("Error: Failed to load font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
//         SDL_DestroyTexture(tex);
//         SDL_DestroyRenderer(render);
//         SDL_DestroyWindow(win);
//         TTF_Quit();
//         SDL_Quit();
//         return 1;
//     }
//     SDL_Color color = {255, 255, 255};


//     // Button setup
//     const int32_t start_button_width = 350, start_button_height = 100;
//     const int32_t start_button_x = (DM.w - start_button_width) / 2, start_button_y = (DM.h - start_button_height);
//     SDL_Rect buttonRect = {start_button_x, start_button_y, start_button_width, start_button_height};
//     // printf("%d %d %d %d\n", start_button_height, start_button_width, start_button_x, start_button_y);

//     int8_t quit = 0;
//     while(!quit){
//         SDL_Event event;
//         while(SDL_PollEvent(&event)){
//             if(event.type == SDL_QUIT){
//                 quit = 1;
//                 break;
//             }
//             else if(event.type == SDL_MOUSEBUTTONDOWN){
//                 int32_t mousex, mousey;
//                 SDL_GetMouseState(&mousex, &mousey);
//                 if(SDL_PointInRect(&(SDL_Point){mousex, mousey}, &buttonRect)){
//                     printf("Button Clicked\n");
//                 }
//             }
//         }

//         SDL_Rect dstrect = {270, 0, 900, 900};
//         // clears the screen
//         SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
//         SDL_RenderClear(render);

//         // Render the window
//         SDL_RenderCopy(render, tex, NULL, &dstrect);
//         SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
//         SDL_RenderFillRect(render, &buttonRect);

//         // triggers the double buffers
//         // for multiple rendering
//         SDL_RenderPresent(render);

//         // calculates to 60 fps
//         SDL_Delay(1000 / 60);
//     }
//     // Basic setup end


//     // close ttf
//     TTF_CloseFont(font);

//     // destroy texture
//     SDL_DestroyTexture(tex);

//     // destroy renderer
//     SDL_DestroyRenderer(render);

//     // destory window
//     SDL_DestroyWindow(win);

//     SDL_Quit();

//     return 0;
// }
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TITLE "Retro Quest"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
SDL_Rect buttonRect = {320, 400, 160, 50}; // 按鈕位置和大小

int initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    font = TTF_OpenFont("font_lib/InflateptxBase-ax3da.ttf", 24); // 字體文件的路徑和大小
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 0;
    }

    return 1;
}

void closeSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // 黑色背景
    SDL_RenderClear(renderer);

    // 繪製標題
    SDL_Color textColor = {255, 255, 255}; // 白色字體顏色
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, TITLE, textColor); // 變化的顏色
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {200, 200, textSurface->w, textSurface->h}; // 標題位置
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

    // 繪製按鈕
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // 灰色按鈕
    SDL_RenderFillRect(renderer, &buttonRect);

    // 更新顯示
    SDL_RenderPresent(renderer);

    // 釋放表面和紋理
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

int main() {
    if (!initSDL()) {
        closeSDL();
        return 1;
    }

    int running = 1;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
                    mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
                    printf("Start button clicked!\n");
                    // 在這裡添加開始遊戲的代碼
                }
            }
        }

        render();
    }

    closeSDL();
    return 0;
}
