#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "ui.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void initSDL();
void cleanupSDL();

int main(int argc, char* argv[]) {
    initSDL();

    SDL_Window* window = SDL_CreateWindow("lifing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int quit = 0;
    SDL_Event e;

    GameState state = STATE_BIRTH;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= 150 && x <= 250 && y >= 450 && y <= 500) {
                    handleChoice(&state, 1);
                } else if (x >= 350 && x <= 450 && y >= 450 && y <= 500) {
                    handleChoice(&state, 2);
                } else if (x >= 550 && x <= 650 && y >= 450 && y <= 500) {
                    handleChoice(&state, 3);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 背包
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect backpackRect = { 20, 20, 50, 50 };
        SDL_RenderFillRect(renderer, &backpackRect);

        // 對話框
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect dialogRect = { 100, 300, 600, 100 };
        SDL_RenderFillRect(renderer, &dialogRect);
        renderText(renderer, getDialogText(state), 120, 320, 560, 60);

        // 選擇按鈕
        renderChoices(renderer);

        // 幸運條
        renderLuckBar(renderer, getLuckValue(state));

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    cleanupSDL();

    return 0;
}

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(1);
    }
}

void cleanupSDL() {
    TTF_Quit();
    SDL_Quit();
}
