#include "gameLoop.h"
#include "utility.h"
#include "constants.h"

int8_t game_loop(SDL_Renderer *renderer){
    int quit = 0;
    SDL_Event e;

    GameState state = STATE_BIRTH;

    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= 150 && x <= 250 && y >= 450 && y <= 500){
                    handleChoice(&state, 1);
                }
                else if(x >= 350 && x <= 450 && y >= 450 && y <= 500){
                    handleChoice(&state, 2);
                }
                else if(x >= 550 && x <= 650 && y >= 450 && y <= 500){
                    handleChoice(&state, 3);
                }
                // else if(x)
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 背包
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect backpackRect = { 20, 20, 50, 50 };
        SDL_RenderFillRect(renderer, &backpackRect);

        // 對話框
        // SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Surface *image = IMG_Load("img/dialog_box.png");
        if(image == NULL){
            printf("Error Read Image: %s\n", SDL_GetError());
            return 0;
        }
        SDL_Rect dialogRect = { 100, 300, 600, 100 };
        // SDL_RenderFillRect(renderer, &dialogRect);
        SDL_Color color = {0, 0, 0};
        rendertext(renderer, "font_lib/Arial.ttf", getDialogText(state), 120, 320, 560, 60, 24, &color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
        SDL_RenderCopy(renderer, texture, NULL, &dialogRect);
        // 選擇按鈕
        renderChoices(renderer);

        // 幸運條
        renderLuckBar(renderer, getLuckValue(state));

        SDL_RenderPresent(renderer);
    }
    return TRUE;
}

void renderChoices(SDL_Renderer* renderer){
    SDL_Color color = {0, 0, 0};
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect choiceRect1 = { 150, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect1);
    rendertext(renderer, "font_lib/Arial.ttf", "rich", 170, 460, 60, 30, 24, &color);

    SDL_Rect choiceRect2 = { 350, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect2);
    rendertext(renderer, "font_lib/Arial.ttf", "poor", 370, 460, 60, 30, 24, &color);

    SDL_Rect choiceRect3 = { 550, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect3);
    rendertext(renderer, "font_lib/Arial.ttf", "orphan", 570, 460, 60, 30, 24, &color);
}

void renderLuckBar(SDL_Renderer* renderer, int luckValue){
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
    SDL_Rect luckBarOutline = { 700, 20, 20, 100 };
    SDL_RenderDrawRect(renderer, &luckBarOutline);
    SDL_Rect luckBar = { 700, 20 + (100 - luckValue), 20, luckValue };
    SDL_RenderFillRect(renderer, &luckBar);
}

void handleChoice(GameState* state, int choice) {
    switch (*state) {
        case STATE_BIRTH:
            if (choice == 1) {
                *state = STATE_CHILDHOOD;
            } else if (choice == 2) {
                *state = STATE_ADULTHOOD;
            } else {
                *state = STATE_OLDAGE;
            }
            break;
        case STATE_CHILDHOOD:
            if (choice == 1) {
                *state = STATE_ADULTHOOD;
            } else if (choice == 2) {
                *state = STATE_OLDAGE;
            } else {
                *state = STATE_END;
            }
            break;
        case STATE_ADULTHOOD:
            if (choice == 1) {
                *state = STATE_OLDAGE;
            } else if (choice == 2) {
                *state = STATE_END;
            } else {
                *state = STATE_END;
            }
            break;
        case STATE_OLDAGE:
            *state = STATE_END;
            break;
        case STATE_END:
            break;
    }
}

const char* getDialogText(GameState state) {
    switch (state) {
        case STATE_BIRTH: return "Please select birth family ~";
        case STATE_CHILDHOOD: return "childhood ~";
        case STATE_ADULTHOOD: return "adulthood ~";
        case STATE_OLDAGE: return "oldage ~";
        case STATE_END: return "end ~";
        default: return "";
    }
}

int getLuckValue(GameState state) {
    switch (state) {
        case STATE_BIRTH: return 70;
        case STATE_CHILDHOOD: return 50;
        case STATE_ADULTHOOD: return 30;
        case STATE_OLDAGE: return 10;
        case STATE_END: return 0;
        default: return 0;
    }
}