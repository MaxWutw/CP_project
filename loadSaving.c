#include "loadSaving.h"

int8_t save(SDL_Renderer *renderer, SDL_DisplayMode *DM, int32_t current_key){
    const char *savingText = "請問您是否確定要存擋？";
    const int32_t savingX = (DM->w - (DM->w / 5) * 4) / 2;
    const int32_t savingY = DM->h - (DM->h / 4) - 200;
    const int32_t savingW = (DM->w / 5) * 4;
    const int32_t savingH = (DM->h / 4) - 50;
    SDL_Color color = {0, 0, 0};
    SDL_Event e;
    int8_t quit = 1;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
            // else if(e.type == SDL_TEXTINPUT){
            //     if(strlen(inputText) + strlen(e.text.text) < sizeof(inputText) - 1){
            //         strcat(inputText, e.text.text);
            //     }
            // }
            // else if(e.type == SDL_KEYDOWN){
            //     if(e.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0){
            //         inputText[strlen(inputText) - 1] = '\0';
            //     } 
            //     else if(e.key.keysym.sym == SDLK_RETURN){
            //         quit = 1;
            //     }
            // }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 132, 243, 155, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect SavingRect = {savingX, savingY, \
            savingW, savingH};
        SDL_RenderFillRect(renderer, &SavingRect);
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            savingText, savingX, \
            savingY, savingW, savingH, 24, &color) == FALSE){
            return 0;
        }
        SDL_RenderPresent(renderer);
    }

    return TRUE;
}

int8_t load(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    // pass
    return TRUE;
}