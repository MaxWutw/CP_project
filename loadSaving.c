#include "loadSaving.h"

int8_t save(SDL_Renderer *renderer, SDL_DisplayMode *DM, int32_t current_key){
    const char *savingText = "請問您是否確定要存檔？";
    // printf("%s\n", savingText);
    const int32_t savingX = (DM->w - (DM->w / 5) * 4) / 2;
    const int32_t savingY = DM->h - (DM->h / 4) - 400;
    const int32_t savingW = (DM->w / 5) * 4;
    const int32_t savingH = (DM->h / 4) - 50;

    const int32_t optionW = (DM->w / 3) - 150;
    const int32_t optionH = (DM->h / 4) - 150;

    const int32_t option1X = ((DM->w - (DM->w / 5) * 4) / 2) + savingW / 3 - optionW;
    const int32_t option1Y = DM->h - (DM->h / 4) - 400 + savingH + 50;
    
    const int32_t option2X = option1X + optionW + savingW / 3;
    const int32_t option2Y = DM->h - (DM->h / 4) - 400 + savingH + 50;

    SDL_Color color = {0, 0, 0};
    SDL_Event e;
    int8_t quit = 0;
    int32_t hover[2] = {0};
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= option1X && x <= option1X + optionW && y >= option1Y && y <= option1Y + optionH){
                    saveData(renderer, DM, current_key);
                    return FALSE;
                }
                else if(x >= option2X && x <= option2X + optionW && y >= option2Y && y <= option2Y + optionH){
                    quit = 1;
                    return TRUE;
                }
            }
            else{
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= option1X && x <= option1X + optionW && y >= option1Y && y <= option1Y + optionH){
                    hover[0] = 1;
                }
                else if(x >= option2X && x <= option2X + optionW && y >= option2Y && y <= option2Y + optionH){
                    hover[1] = 1;
                }
                else{
                    hover[0] = 0;
                    hover[1] = 0;
                }
            }
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
            savingY, savingW, savingH, 48, &color) == FALSE){
            return FALSE;
        }

        SDL_Rect option1Rect = {option1X, option1Y, optionW, optionH};
        SDL_Rect option2Rect = {option2X, option2Y, optionW, optionH};
        if(hover[0]){
            SDL_SetRenderDrawColor(renderer, 38, 90, 250, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 38, 201, 250, 255);
        }
        SDL_RenderFillRect(renderer, &option1Rect);
        rendertext(renderer, "font_lib/biakai.ttf", "確定", \
        option1X + (optionW / 2) - 40, option1Y, optionW , optionH, 38, &color);

        if(hover[1]){
            SDL_SetRenderDrawColor(renderer, 38, 90, 250, 255);
        }
        else{
            SDL_SetRenderDrawColor(renderer, 38, 201, 250, 255);
        }
        SDL_RenderFillRect(renderer, &option2Rect);
        rendertext(renderer, "font_lib/biakai.ttf", "取消", \
        option2X + (optionW / 2) - 40, option2Y, optionW , optionH, 38, &color);

        SDL_RenderPresent(renderer);


    }

    return TRUE;
}

int8_t load(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    // pass
    return TRUE;
}

int8_t saveData(SDL_Renderer *renderer, SDL_DisplayMode *DM, int32_t current_key){
    char *text = NULL;
    SDL_Color color = {0, 0, 0};
    const int32_t dialogX = (DM->w - (DM->w / 5) * 4) / 2;
    const int32_t dialogY = DM->h - (DM->h / 4) - 200;
    const int32_t dialogW = (DM->w / 5) * 4;
    const int32_t dialogH = (DM->h / 4) - 50;
    userInpStr(renderer, DM, &text, "font_lib/biakai.ttf", "你想要將除存檔命名成什麼：", \
    dialogX, dialogY, dialogW, dialogH);
    char filename[256];
    snprintf(filename, sizeof(filename), "%s.json", text);
    FILE *pFile = NULL;
    if((pFile = fopen(filename, "w")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return FALSE;
    }
    char jsonData[256];
    snprintf(jsonData, sizeof(jsonData), "{\"NTNUFINAL\":,\"KeyValue\":%d}", current_key);
    fwrite(jsonData, strlen(jsonData), 1, pFile);
    fclose(pFile);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 145, 252, 248, 0xFF);
    SDL_Rect dialogRect = {dialogX, dialogY, dialogW, dialogH};
    SDL_RenderFillRect(renderer, &dialogRect);
    char endText[512];
    snprintf(endText, sizeof(endText), "存檔成功，紀錄檔名稱為： %s，感謝您的遊玩，下次見！ 按任何鍵結束遊戲。", filename);
    free(text);
    int8_t quit = 0;
    SDL_Event e;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_KEYDOWN){
                quit = 1;
                return FALSE;
            }
        }
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            endText, dialogX, \
            dialogY, dialogW, 0, 24, &color) == FALSE){
            return 0;
        }
    }

    return TRUE;
}


// int8_t loadData(int32_t){
//     // pass
//     return TRUE;
// }