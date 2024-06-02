#include "backpack.h"
#include "utility.h"
#include "constants.h"

int8_t backpack_interface(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    int8_t quit = 0;
    while(!quit){
        // SDL_SetRenderDrawColor(renderer, 91, 245, 173, 0xFF);
        // SDL_RenderClear(renderer);

        int windowWidth = DM->w;
        int windowHeight = DM->h;
        int backpackWidth = windowWidth / 2;
        int backpackHeight = windowHeight - 100;
        int backpackX = (windowWidth - backpackWidth) / 2;
        int backpackY = (windowHeight - backpackHeight) / 2;

        SDL_Rect backpackRect = {backpackX, 20, backpackWidth, backpackHeight };

        // side
        SDL_SetRenderDrawColor(renderer, 91, 245, 173, 0xFF);
        SDL_RenderFillRect(renderer, &backpackRect);

        int portraitSize = backpackWidth / 4;
        SDL_Rect portraitRect = {backpackX + backpackWidth / 20, backpackY, portraitSize, portraitSize};

        // head
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderFillRect(renderer, &portraitRect);

        // SDL_Rect personInfoRect = {backpackX + backpackWidth / 20 + portraitSize, backpackY, portraitSize, portraitSize};
        // person info
        SDL_Rect personInfoRect = {backpackX + backpackWidth / 20 + portraitSize + 50, backpackY, backpackWidth - (backpackWidth / 20 + portraitSize + 50) - 50, portraitSize + 50};
        SDL_RenderDrawRect(renderer, &personInfoRect);
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        int32_t InfoStartX = backpackX + backpackWidth / 20 + portraitSize + 50, InfoStartY = backpackY;

        char deposit_output[100];
        snprintf(deposit_output, sizeof(deposit_output), "銀子： %d 兩銀子", calPersonDeposit());
        rendertext(renderer, "font_lib/biakai.ttf", deposit_output, InfoStartX + 25, InfoStartY + 10, 0, 0, 24, &textColor);
        char curStatus[100];
        snprintf(curStatus, sizeof(curStatus), "位階： %s", PersonCurStatus());
        rendertext(renderer, "font_lib/biakai.ttf", curStatus, InfoStartX + 25, InfoStartY + 46, 0, 0, 24, &textColor);
        
        // close
        int32_t closeX = backpackX + backpackWidth - 40, closeY = backpackY - 10, closeSize = 30;
        SDL_Rect closeRect = {closeX, closeY, closeSize, closeSize};
        SDL_Surface *close = IMG_Load("img/close.png");
        if(close == NULL){
            printf("Error Read Image: %s\n", SDL_GetError());
            return 0;
        }

        SDL_Texture *close_texture = SDL_CreateTextureFromSurface(renderer, close);
        SDL_RenderCopy(renderer, close_texture, NULL, &closeRect);
        SDL_FreeSurface(close);
        SDL_DestroyTexture(close_texture);

        // name
        rendertext(renderer, "font_lib/biakai.ttf", "韋小寶", backpackX + backpackWidth / 20 + portraitSize / 2 - 40, portraitRect.y + portraitRect.h + 10, 0, 0, 24, &textColor);

        int gridCols = 5;
        int gridRows = 4;
        int gridCellSize = (backpackWidth - 40) / gridCols - 50; 
        int gridX = backpackX + (backpackWidth - (gridCols * gridCellSize + (gridCols - 1) * 30)) / 2; // 30 代表空隙
        int gridY = portraitRect.y + portraitRect.h + 10 + 50;

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        for(int row = 0;row < gridRows;row++){
            for(int col = 0;col < gridCols;col++){
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX > gridX + col * (gridCellSize + 30) && mouseX < gridX + col * (gridCellSize + 30) + gridCellSize && \
                    mouseY > gridY + row * (gridCellSize + 30) && mouseY < gridY + row * (gridCellSize + 30) + gridCellSize){
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 154, 154, 154, 0xFF);
                }

                SDL_Rect cellRect = {gridX + col * (gridCellSize + 30), gridY + row * (gridCellSize + 30), gridCellSize, gridCellSize};
                SDL_RenderDrawRect(renderer, &cellRect);
            }
        }

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(event.type == SDL_QUIT){
                quit = 1;
                // return FALSE;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                if(mouseX > closeX && mouseX < closeX + closeSize && \
                    mouseY > closeY && mouseY < closeY + closeSize){
                    openBackPack = 0;
                    quit = 1;
                    // return TRUE;
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}

int32_t calPersonDeposit(){
    // pass
    return 100;
}

char* PersonCurStatus(){
    return "可憐書生";
}