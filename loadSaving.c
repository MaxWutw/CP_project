#include "loadSaving.h"

static int32_t loadFileCnt = 0;
static int8_t __getPlayerName(const char *, char **);
static int8_t __getKeyValue(const char *, int32_t *);
static int8_t __getInventory(const char *, char **);
static int32_t __str2int(const char *);
static int8_t __applyCurState(char *, const char *, const int32_t *, const int32_t *,\
                              int32_t *, int32_t *, Item [100], Npc [100], sBackPack *);
static int8_t __parseIvent(const char *, int32_t **, int32_t *);
static int8_t __getLuckyValue(const char *, int32_t *);
int8_t save(SDL_Renderer *renderer, SDL_DisplayMode *DM, int32_t current_key, sBackPack *backpack, int32_t luck_val){
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
                    saveData(renderer, DM, current_key, backpack, luck_val);
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

int8_t load(SDL_Renderer *renderer, SDL_DisplayMode *DM, \
            int32_t *current_key, int32_t *luck_val, Item items[100], Npc npcs[100], sBackPack *backpack){
    const char *loadingText = "請選擇你想要開啟的儲存檔";
    const int32_t loadingX = (DM->w - (DM->w / 5) * 4) / 2;
    const int32_t loadingY = DM->h - (DM->h / 4) - 550;
    const int32_t loadingW = (DM->w / 5) * 4;
    const int32_t loadingH = (DM->h / 4) - 50;

    const int32_t optionW = (DM->w / 3) + 100;
    const int32_t optionH = (DM->h / 4);

    const int32_t option1X = ((DM->w - (DM->w / 5) * 4) / 2) + loadingW / 3 - (optionW / 5);
    const int32_t option1Y = DM->h - (DM->h / 4) - 500 + loadingH;

    const int32_t controlW = (DM->w / 3) - (DM->w / 5.48571); // fix
    const int32_t controlH = (DM->h / 4) - (DM->h / 5.4); // fix

    const int32_t nextX = ((DM->w - (DM->w / 5) * 4) / 2) + loadingW / 3 - controlW + 30;
    const int32_t nextY = DM->h - (DM->h / 4) - 200 + loadingH + 50;

    const int32_t selectX = nextX + controlW + 30;
    const int32_t selectY = DM->h - (DM->h / 4) - 200 + loadingH + 50;

    const int32_t backX = selectX + controlW + 30;
    const int32_t backY = DM->h - (DM->h / 4) - 200 + loadingH + 50;
    int8_t hover[3] = {0};

    char *Playername = NULL, *invent = NULL;
    int32_t keyValue = 0, LuckyValue = 0;
    
    int32_t dialogX = (DM->w - (DM->w / 5) * 4) / 2;
    int32_t dialogY = DM->h - (DM->h / 4) - 200;
    int32_t dialogW = (DM->w / 5) * 4;
    int32_t dialogH = (DM->h / 4) - 50;

    char filenameArr[512][512];
    loadFromJson(filenameArr);
    for(int32_t i = 0;i < loadFileCnt;i++) printf("%s\n", filenameArr[i]);

    SDL_Color color = {0, 0, 0};
    SDL_Event e;
    int8_t quit = 0;
    int32_t current_select = 0;
    int8_t slideLeft = 0, slideRight = 0;
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
                return FALSE;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= nextX && x <= nextX + controlW && y >= nextY && y <= nextY + controlH){
                    slideRight = (current_select - 1 < 0) ? 0 : 1;
                    current_select = (current_select - 1 < 0) ? current_select : current_select - 1;
                    // SDL_Rect BlockRect = {loadingX, loadingY, loadingW, loadingH};
                    // option1X, option1Y, optionW , optionH,
                }
                else if(x >= selectX && x <= selectX + controlW && y >= selectY && y <= selectY + controlH){
                    __applyCurState(Playername, invent, &keyValue, &LuckyValue, \
                    current_key, luck_val, items, npcs, backpack);
                    finish = 1;
                    char toPlayer[1024];
                    snprintf(toPlayer, sizeof(toPlayer), "成功讀取 %s 之資料！", filenameArr[current_select]);
                    // printBackpackItem(backpack);
                    // printf("%d %d\n", *current_key, *luck_val);
                    SDL_SetRenderDrawColor(renderer, 145, 252, 248, 0xFF);
                    // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
                    SDL_Rect dialogRect = {dialogX, dialogY, dialogW, dialogH};
                    SDL_RenderFillRect(renderer, &dialogRect);
                    if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
                        toPlayer, dialogX, \
                        dialogY, dialogW, 0, 38, &color) == FALSE){
                        return 0;
                    }
                    SDL_RenderPresent(renderer);
                    SDL_Delay(3000);
                    return TRUE;
                }
                else if(x >= backX && x <= backX + controlW && y >= backY && y <= backY + controlH){
                    slideLeft = (current_select + 1 >= loadFileCnt) ? 0 : 1;
                    current_select = (current_select + 1 >= loadFileCnt) ? current_select : current_select + 1;
                }
            }
            else{
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= nextX && x <= nextX + controlW && y >= nextY && y <= nextY + controlH){
                    hover[0] = 1;
                    hover[1] = 0;
                    hover[2] = 0;
                }
                else if(x >= selectX && x <= selectX + controlW && y >= selectY && y <= selectY + controlH){
                    hover[1] = 1;
                    hover[0] = 0;
                    hover[2] = 0;
                }
                else if(x >= backX && x <= backX + controlW && y >= backY && y <= backY + controlH){
                    hover[2] = 1;
                    hover[0] = 0;
                    hover[1] = 0;
                }
                else{
                    hover[0] = 0;
                    hover[1] = 0;
                    hover[2] = 0;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 132, 243, 155, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect LoadingRect = {loadingX, loadingY, \
            loadingW, loadingH};
        SDL_RenderFillRect(renderer, &LoadingRect);
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            loadingText, loadingX, \
            loadingY, loadingW, loadingH, 48, &color) == FALSE){
            return FALSE;
        }

        SDL_Rect option1Rect = {option1X, option1Y, optionW, optionH};
        // if(hover[0]){
        //     SDL_SetRenderDrawColor(renderer, 38, 90, 250, 255);
        // }
        // else{
            SDL_SetRenderDrawColor(renderer, 38, 201, 250, 255);
        // }
        SDL_RenderFillRect(renderer, &option1Rect);
        rendertext(renderer, "font_lib/biakai.ttf", filenameArr[current_select], \
        option1X, option1Y, optionW , optionH, 38, &color);

        if(slideLeft || slideRight){
            int32_t step = optionW / (300 / 16);
            int32_t startX = option1X;
            int32_t endX = (slideLeft == 0 ? DM->w : 0);
            Mix_Chunk *soundEffect = NULL;
            PlayChunk("music/fly.mp3", soundEffect, -1, MIX_MAX_VOLUME, 0);
            for(int32_t x = startX, x2 = (slideLeft == 0 ? -optionW : DM->w);\
                (slideLeft == 0 ? x < DM->w + optionW : x > endX - optionW) \
                && (slideLeft == 0 ? x2 < option1X : x2 < DM->w + optionW); \
                x += (slideLeft == 0 ? step : -step), x2 += (slideLeft == 0 ? step : -step)){
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
                SDL_RenderClear(renderer);
                // basic
                SDL_SetRenderDrawColor(renderer, 132, 243, 155, 0xFF);
                // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
                SDL_Rect LoadingRect = {loadingX, loadingY, \
                    loadingW, loadingH};
                SDL_RenderFillRect(renderer, &LoadingRect);
                if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
                    loadingText, loadingX, \
                    loadingY, loadingW, loadingH, 48, &color) == FALSE){
                    return FALSE;
                }

                if(hover[0]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
                else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
                SDL_Rect nextRect = {nextX, nextY, controlW, controlH};
                SDL_RenderFillRect(renderer, &nextRect);
                rendertext(renderer, "font_lib/biakai.ttf", "上一個", \
                        nextX, nextY, controlW , controlH, 58, &color);

                if(hover[1]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
                else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
                SDL_Rect selectRect = {selectX, selectY, controlW, controlH};
                SDL_RenderFillRect(renderer, &selectRect);
                rendertext(renderer, "font_lib/biakai.ttf", "確認", \
                        selectX, selectY, controlW , controlH, 58, &color);

                if(hover[2]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
                else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
                SDL_Rect backRect = {backX, backY, controlW, controlH};
                SDL_RenderFillRect(renderer, &backRect);
                rendertext(renderer, "font_lib/biakai.ttf", "下一個", \
                        backX, backY, controlW , controlH, 58, &color);
                // basic end;

                SDL_SetRenderDrawColor(renderer, 38, 201, 250, 255);
                // printf("%d %d %d %d\n", x, option1Y, optionW , optionH);
                SDL_Rect tmpRect = {x, option1Y, optionW , optionH};
                SDL_Rect tmp2Rect = {x2, option1Y, optionW , optionH};
                SDL_RenderFillRect(renderer, &tmpRect);
                SDL_RenderFillRect(renderer, &tmp2Rect);
                SDL_RenderPresent(renderer);
                SDL_Delay(16);
            }
            slideLeft = 0;
            slideRight = 0;
            Mix_HaltChannel(-1);
            if(soundEffect == NULL) Mix_FreeChunk(soundEffect);
        }

        // char *Playername = NULL, *invent = NULL;
        // int32_t keyValue = 0;
        if( __getPlayerName(filenameArr[current_select], &Playername) == TRUE){
            // printf("%s\n", Playername);
            char _name[256];
            snprintf(_name, sizeof(_name), "Player Name: %s", Playername);
            rendertext(renderer, "font_lib/biakai.ttf", _name, \
                option1X, option1Y + 40, optionW , optionH, 38, &color);
            // free(Playername);
        }
        if( __getKeyValue(filenameArr[current_select], &keyValue) == TRUE ){
            // printf("%d\n", keyValue);
        }
        if( __getLuckyValue(filenameArr[current_select], &LuckyValue) == TRUE ){
            // printf("%d\n", keyValue);
            char lucky[256];
            snprintf(lucky, sizeof(lucky), "Lucky Value: %d", LuckyValue);
            rendertext(renderer, "font_lib/biakai.ttf", lucky, \
                option1X, option1Y + 80, optionW , optionH, 38, &color);
        }
        if( __getInventory(filenameArr[current_select], &invent) == TRUE){
            // printf("%s\n", invent);
            char _invent[256];
            snprintf(_invent, sizeof(_invent), "Player Inventory: %s", invent);
            rendertext(renderer, "font_lib/biakai.ttf", _invent, \
                option1X, option1Y + 120, optionW , optionH, 38, &color);
            // free(invent);
        }

        if(hover[0]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
        else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
        SDL_Rect nextRect = {nextX, nextY, controlW, controlH};
        SDL_RenderFillRect(renderer, &nextRect);
        rendertext(renderer, "font_lib/biakai.ttf", "上一個", \
                nextX, nextY, controlW , controlH, 58, &color);

        if(hover[1]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
        else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
        SDL_Rect selectRect = {selectX, selectY, controlW, controlH};
        SDL_RenderFillRect(renderer, &selectRect);
        rendertext(renderer, "font_lib/biakai.ttf", "確認", \
                selectX, selectY, controlW , controlH, 58, &color);

        if(hover[2]) SDL_SetRenderDrawColor(renderer, 201, 0, 129, 0xFF);
        else SDL_SetRenderDrawColor(renderer, 255, 87, 194, 0xFF);
        SDL_Rect backRect = {backX, backY, controlW, controlH};
        SDL_RenderFillRect(renderer, &backRect);
        rendertext(renderer, "font_lib/biakai.ttf", "下一個", \
                backX, backY, controlW , controlH, 58, &color);

        // printf("%s\n%d\n%s\n", Playername, keyValue, invent);

        SDL_RenderPresent(renderer);
    }
    if(Playername != NULL) free(Playername);
    if(invent != NULL) free(invent);

    return TRUE;
}

int8_t saveData(SDL_Renderer *renderer, SDL_DisplayMode *DM, int32_t current_key, sBackPack *backpack, int32_t luck_val){
    char *text = NULL;
    SDL_Color color = {0, 0, 0};
    const int32_t dialogX = (DM->w - (DM->w / 5) * 4) / 2;
    const int32_t dialogY = DM->h - (DM->h / 4) - 200;
    const int32_t dialogW = (DM->w / 5) * 4;
    const int32_t dialogH = (DM->h / 4) - 50;
    userInpStr(renderer, DM, &text, "font_lib/biakai.ttf", "你想要將除存檔命名成什麼：", \
    dialogX, dialogY, dialogW, dialogH);
    char filename[256];
    snprintf(filename, sizeof(filename), "DataSave/%s.json", text);
    save2json(backpack, current_key, filename, luck_val);
    
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


int8_t save2json(sBackPack *backpack, int32_t current_key, char *filename, int32_t luck_val){
    FILE *pFile = NULL;
    if((pFile = fopen(filename, "w")) == NULL){
        fprintf(stderr, "Error: Unable to open file for reading or writing\n");
        return FALSE;
    }
    char jsonData[1024];
    snprintf(jsonData, sizeof(jsonData), "{\n\t\"NTNUFINAL\":%d,\n\t\"PlayerName\":\"%s\",\n\t\"KeyValue\":%d,\n\t\"LuckyValue\":%d,\n", 2147483647, get_player_name(), current_key, luck_val);
    fwrite(jsonData, strlen(jsonData), 1, pFile);

    snprintf(jsonData, sizeof(jsonData), "\t\"Inventory\":[");
    fwrite(jsonData, strlen(jsonData), 1, pFile);
    sListNode *pNode = backpack->pHead;
    int8_t first = 1;
    while(pNode != NULL){
        if(first){
            snprintf(jsonData, sizeof(jsonData), "%d", pNode->pData->id);
            first = 0;
        }
        else{
            snprintf(jsonData, sizeof(jsonData), ",%d", pNode->pData->id);
        }
        fwrite(jsonData, strlen(jsonData), 1, pFile);
        pNode = pNode->pNext;
    }

    snprintf(jsonData, sizeof(jsonData), "]\n");
    fwrite(jsonData, strlen(jsonData), 1, pFile);

    snprintf(jsonData, sizeof(jsonData), "}");
    fwrite(jsonData, strlen(jsonData), 1, pFile);
    fclose(pFile);
    return TRUE;
}

int8_t loadFromJson(char filenameArr[512][512]){
    DIR *dir;
    struct dirent *entry;
    const char *DIRECTORY_PATH = "DataSave";
    const char *FILE_BASE = ".json";

    // Open the directory
    if((dir = opendir(DIRECTORY_PATH)) == NULL){
        perror("Error opening directory");
        return EXIT_FAILURE;
    }

    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_REG && strstr(entry->d_name, FILE_BASE) != NULL){
            char file_path[512];
            snprintf(file_path, sizeof(file_path), "%s/%s", DIRECTORY_PATH, entry->d_name);
            process_file(file_path, filenameArr);
        }
    }
    
    closedir(dir);

    return TRUE;
}

int8_t process_file(const char *file_path, char filenameArr[512][512]){
    const char *keyChar = "\"NTNUFINAL\":2147483647,";

    FILE *pFile = fopen(file_path, "r");
    if(pFile == NULL){
        perror("Error opening file");
        return FALSE;
    }
    char buffer[512];
    int8_t isSave = 0;
    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        // printf("%s\n", buffer);
        if(strstr(buffer, keyChar) != NULL){
            isSave = 1;
        }
    }
    if(isSave){
        strcpy(filenameArr[loadFileCnt], file_path);
        loadFileCnt++;
    }

    fclose(pFile);
    return TRUE;
}

static int8_t __getPlayerName(const char *file_path, char **Playername){
    const char *keyChar = "PlayerName";
    FILE *pFile = fopen(file_path, "r");
    if(pFile == NULL){
        perror("Error opening file");
        return FALSE;
    }
    char buffer[512], tmp[512];
    int8_t isFind = 0;
    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        if(strstr(buffer, keyChar) != NULL){
            if( sscanf(buffer, "%*[^:]:\"%[^\"]\",", tmp) == 1 ){
                *Playername = malloc(strlen(tmp) + 1);
                if(*Playername == NULL) {
                    perror("Error allocating memory");
                    fclose(pFile);
                    return FALSE;
                }
                strcpy(*Playername, tmp);
                // *Playername = tmp;
                // printf("%s\n", *Playername);
                isFind = 1;
            }
        }
    }
    fclose(pFile);
    return (isFind ? TRUE : FALSE);
}

static int8_t __getKeyValue(const char *file_path, int32_t *keyValue){
    const char *keyChar = "KeyValue";
    FILE *pFile = fopen(file_path, "r");
    if(pFile == NULL){
        perror("Error opening file");
        return FALSE;
    }
    char buffer[512], tmp[512];
    int8_t isFind = 0;
    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        if(strstr(buffer, keyChar) != NULL){
            if( sscanf(buffer, "%*[^:]:%[^,],", tmp) == 1 ){
                *keyValue = __str2int(tmp);
                // printf("%d\n", *keyValue);
                isFind = 1;
            }
        }
    }
    fclose(pFile);
    return (isFind ? TRUE : FALSE);
}

static int8_t __getLuckyValue(const char *file_path, int32_t *LuckyValue){
    const char *keyChar = "LuckyValue";
    FILE *pFile = fopen(file_path, "r");
    if(pFile == NULL){
        perror("Error opening file");
        return FALSE;
    }
    char buffer[512], tmp[512];
    int8_t isFind = 0;
    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        if(strstr(buffer, keyChar) != NULL){
            if( sscanf(buffer, "%*[^:]:%[^,],", tmp) == 1 ){
                *LuckyValue = __str2int(tmp);
                // printf("%d\n", *keyValue);
                isFind = 1;
            }
        }
    }
    fclose(pFile);
    return (isFind ? TRUE : FALSE);
}

static int8_t __getInventory(const char *file_path, char **invent){
    const char *keyChar = "Inventory";
    FILE *pFile = fopen(file_path, "r");
    if(pFile == NULL){
        perror("Error opening file");
        return FALSE;
    }
    char buffer[512], tmp[512];
    int8_t isFind = 0;
    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        if(strstr(buffer, keyChar) != NULL){
            if( sscanf(buffer, "%*[^:]:%s", tmp) == TRUE ){
                *invent = malloc(strlen(tmp) + 1);
                // strcpy(invent, tmp);
                if(*invent == NULL) {
                    perror("Error allocating memory");
                    fclose(pFile);
                    return FALSE;
                }
                strcpy(*invent, tmp);
                // *invent = tmp;
                // printf("%s\n", *invent);
                isFind = 1;
            }
        }
    }
    fclose(pFile);
    return (isFind ? TRUE : FALSE);
}

static int32_t __str2int(const char *str){
    int32_t ret = 0;
    for(const char *it = str;*it != '\0';it++){
        ret = (ret * 10) + (*it - '0');
    }
    return ret;
}

static int8_t __applyCurState(char *Playername, const char *invent, const int32_t *keyValue, const int32_t *LuckyValue, \
            int32_t *current_key, int32_t *luck_val, Item items[100], Npc npcs[100], sBackPack *backpack){
    set_player_name(Playername);
    // printf("invent: %s\n", invent);
    *current_key = *keyValue;
    *luck_val = *LuckyValue;
    int32_t *arr = NULL, inventSize = 0;
    __parseIvent(invent, &arr, &inventSize);
    for(int32_t i = 0;i < inventSize;i++){
        AddItemToBackpack(backpack, &items[arr[i] - 1]);
    }
    // printBackpackItem(backpack);
    
    return TRUE;
}

static int8_t __parseIvent(const char *input, int32_t **output_array, int32_t *output_size){
    int32_t *array = NULL;
    int32_t size = 0;
    int32_t capacity = 10;
    array = (int32_t *)malloc(capacity * sizeof(int32_t));
    if(array == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        return FALSE;
    }

    const char *ptr = input;

    if(*ptr != '['){
        fprintf(stderr, "Invalid input format\n");
        free(array);
        return FALSE;
    }
    ptr++;

    while(*ptr != ']' && *ptr != '\0'){
        while(*ptr != '\0' && !isdigit(*ptr) && *ptr != '-'){
            ptr++;
        }
        if(isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))){
            int32_t num = strtol(ptr, (char **)&ptr, 10);

            if(size >= capacity){
                capacity *= 2;
                array = (int32_t *)realloc(array, capacity * sizeof(int32_t));
                if(array == NULL){
                    fprintf(stderr, "Memory allocation failed\n");
                    return FALSE;
                }
            }
            array[size++] = num;
        }
    }

    *output_array = array;
    *output_size = size;
    return TRUE;
}