#include "userInput.h"

int8_t userInpName(SDL_Renderer *renderer, SDL_DisplayMode *DM, char **text, const char* font_path, const char *str2user){
    int32_t fontSize = 24;
    TTF_Font* font = TTF_OpenFont(font_path, fontSize); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }

    SDL_StartTextInput();
    int8_t quit = 0;
    SDL_Event e;
    char inputText[128] = "";
    SDL_Color color = {0, 0, 0};
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                // quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_TEXTINPUT){
                if(strlen(inputText) + strlen(e.text.text) < sizeof(inputText) - 1){ // add to the back
                    strcat(inputText, e.text.text);
                }
            }
            else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0){ // delete
                    inputText[strlen(inputText) - 1] = '\0';
                } 
                else if(e.key.keysym.sym == SDLK_RETURN){
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 132, 243, 155, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect dialogRect = {(DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 200, \
         (DM->w / 5) * 4, (DM->h / 4) - 50};
        SDL_RenderFillRect(renderer, &dialogRect);
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            str2user, (DM->w - (DM->w / 5) * 4) / 2, \
            DM->h - (DM->h / 4) - 200, (DM->w / 5) * 4, 0, 24, &color) == FALSE ){
            return FALSE;
        }
        
        if(strcmp(inputText, "") != 0) rendertext(renderer, "font_lib/Arial.ttf", inputText, \
        (DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 200 + 25, DM->w , DM->h, fontSize, &color);
        SDL_RenderPresent(renderer);
    }
    finish = 1;
    SDL_StopTextInput();
    TTF_CloseFont(font);
    printf("You entered: %s\n", inputText);
    set_player_name(inputText);
    return TRUE;
}

int8_t userInpStr(SDL_Renderer *renderer, SDL_DisplayMode *DM, char **text, const char* font_path, const char *str2user,\
                    int32_t blockx, int32_t blocky, int32_t blockw, int32_t blockh){
    int32_t fontSize = 24;
    TTF_Font* font = TTF_OpenFont(font_path, fontSize); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }
    *text = malloc(1000);
    SDL_StartTextInput();
    int8_t quit = 0;
    SDL_Event e;
    char inputText[128] = "";
    SDL_Color color = {0, 0, 0};
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                // quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_TEXTINPUT){
                if(strlen(inputText) + strlen(e.text.text) < sizeof(inputText) - 1){ // add to the back
                    strcat(inputText, e.text.text);
                }
            }
            else if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0){ // delete
                    inputText[strlen(inputText) - 1] = '\0';
                } 
                else if(e.key.keysym.sym == SDLK_RETURN){
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 132, 243, 155, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect dialogRect = {blockx, blocky, blockw, blockh};
        SDL_RenderFillRect(renderer, &dialogRect);
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            str2user, blockx, blocky, blockw, blockh, 24, &color) == FALSE ){
            return FALSE;
        }
        
        if(strcmp(inputText, "") != 0) rendertext(renderer, "font_lib/Arial.ttf", inputText, \
        blockx, blocky + 25, blockw , blockh, fontSize, &color);
        SDL_RenderPresent(renderer);
    }
    finish = 1;
    SDL_StopTextInput();
    TTF_CloseFont(font);
    strcpy(*text, inputText);
    return TRUE;
}