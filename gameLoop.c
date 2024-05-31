#include "gameLoop.h"
#include "utility.h"
#include "constants.h"
#include "toml_parse.h"
#include "freshNewScreen.h"

int8_t game_loop(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    int quit = 0;
    SDL_Event e;
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    GameState state = STATE_BIRTH;
    int8_t hover[3] = {0};
    int32_t option[3], current_key = 6;
    int32_t ret = get_option(pFile, current_key, option);
    if(ret != 0){
        printf("end of story\n");
        return 0;
    }
    // int8_t finish = 1;

    SDL_Rect img = {0, 0, DM->w, DM->h};
    SDL_Surface *bg = IMG_Load("img/background.jpg");
    if(bg == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg);
    SDL_RenderCopy(renderer, bg_texture, NULL, &img);
    SDL_FreeSurface(bg);
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= 30 && x <= 30 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 1);
                    current_key = option[0];
                }
                else if(x >= 80 + (DM->w / 3) - 50 && x <= 80 + (DM->w / 3) - 50 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 2);
                    current_key = option[1];
                }
                else if(x >= 120 + ((DM->w / 3) - 50) * 2 && x <= 120 + ((DM->w / 3) - 50) * 2 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 3);
                    current_key = option[2];
                }
            }
            else{
                int x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= 30 && x <= 30 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *hover = 1;
                }
                else if(x >= 80 + (DM->w / 3) - 50 && x <= 80 + (DM->w / 3) - 50 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *(hover + 1) = 1;
                }
                else if(x >= 120 + ((DM->w / 3) - 50) * 2 && x <= 120 + ((DM->w / 3) - 50) * 2 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *(hover + 2) = 1;
                }
                else{
                    for(int32_t i = 0;i < 3;i++) *(hover + i) = 0;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        // 背景
        // SDL_Rect img = {0, 0, DM->w, DM->h};
        // SDL_Surface *bg = IMG_Load("img/background.jpg");
        // if(bg == NULL){
        //     printf("Error Read Image: %s\n", SDL_GetError());
        //     return 0;
        // }

        // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, bg);
        // SDL_RenderCopy(renderer, texture, NULL, &img);
        // SDL_FreeSurface(bg);
        SDL_RenderCopy(renderer, bg_texture, NULL, &img);
        renderCharacter(renderer, DM, "img/street_fighter.png");
        // renderAvatar(renderer, DM, "img/street_fighter_avatar.jpg");
        // 背包
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect backpackRect = {20, 20, 50, 50};
        SDL_RenderFillRect(renderer, &backpackRect);
        // 對話框
        SDL_SetRenderDrawColor(renderer, 145, 252, 248, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect dialogRect = {(DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 150, (DM->w / 5) * 4, (DM->h / 4) - 50};
        SDL_RenderFillRect(renderer, &dialogRect);
        SDL_Color color = {0, 0, 0};
        char *text_name = NULL;
        if( get_text(pFile, current_key, &text_name) == 1 ){
            return FALSE;
        }
        // rendertext_per_sec(renderer, "font_lib/biakai.ttf", text_name, (DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 150, 750, 60, 24, &color);
        rendertext(renderer, "font_lib/biakai.ttf", text_name, (DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 150, 750, 60, 24, &color);
        SDL_RenderDrawRect(renderer, &dialogRect);
        
        
        // 選擇按鈕
        
        // printf("%d %d %d\n", option[0], option[1], option[2]);
        if( get_option(pFile, current_key, option) == 1 ){
            return FALSE;
        }
        char *str1 = NULL, *str2 = NULL, *str3 = NULL;
        if( get_title(pFile, option[0], &str1) == 1 ){
            return FALSE;
        }
        if( get_title(pFile, option[1], &str2) == 1 ){
            return FALSE;
        }
        if( get_title(pFile, option[2], &str3) == 1 ){
            return FALSE;
        }
        renderChoices(renderer, str1, str2, str3, DM, hover);
        if(str1 != NULL) free(str1);
        if(str2 != NULL) free(str2);
        if(str3 != NULL) free(str3);
        // 幸運條
        renderLuckBar(renderer, getLuckValue(state), DM);

        SDL_RenderPresent(renderer);
        if(text_name != NULL) free(text_name);
    }
    SDL_DestroyTexture(bg_texture);
    return TRUE;
}

void renderChoices(SDL_Renderer* renderer, const char* option1, const char* option2, const char* option3, SDL_DisplayMode *DM, int8_t *hover){
    SDL_Color color = {0, 0, 0};
    if(*hover == 0) SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    SDL_Rect choiceRect1 = {30, DM->h - (DM->h / 4) + 30, (DM->w / 3) - 50, (DM->h / 4) - 100};
    SDL_RenderDrawRect(renderer, &choiceRect1);
    rendertext(renderer, "font_lib/biakai.ttf", option1, 30, DM->h - (DM->h / 4) + 30, 200, 30, 24, &color);

    if(*(hover + 1) == 0) SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    SDL_Rect choiceRect2 = {80 + (DM->w / 3) - 50, DM->h - (DM->h / 4) + 30, (DM->w / 3) - 50, (DM->h / 4) - 100};
    SDL_RenderDrawRect(renderer, &choiceRect2);
    rendertext(renderer, "font_lib/biakai.ttf", option2, 80 + (DM->w / 3) - 50, DM->h - (DM->h / 4) + 30, 200, 30, 24, &color);

    if(*(hover + 2) == 0) SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    else SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    SDL_Rect choiceRect3 = {120 + ((DM->w / 3) - 50) * 2, DM->h - (DM->h / 4) + 30, (DM->w / 3) - 50, (DM->h / 4) - 100};
    SDL_RenderDrawRect(renderer, &choiceRect3);
    rendertext(renderer, "font_lib/biakai.ttf", option3, 120 + ((DM->w / 3) - 50) * 2, DM->h - (DM->h / 4) + 30, 200, 30, 24, &color);
}

void renderLuckBar(SDL_Renderer* renderer, int luckValue, SDL_DisplayMode *DM){
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
    SDL_Rect luckBarOutline = {DM->w - 100, 20, 50, 400};
    SDL_RenderDrawRect(renderer, &luckBarOutline);
    SDL_Rect luckBar = { DM->w - 100, 20 + (400 - luckValue), 50, luckValue };
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

int getLuckValue(GameState state) {
    switch (state) {
        case STATE_BIRTH: return 370;
        case STATE_CHILDHOOD: return 250;
        case STATE_ADULTHOOD: return 130;
        case STATE_OLDAGE: return 50;
        case STATE_END: return 0;
        default: return 0;
    }
}