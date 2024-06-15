#include "gameLoop.h"
#include "utility.h"
#include "constants.h"
#include "toml_parse.h"
#include "toml_parse_item.h"
#include "freshNewScreen.h"
// #include "backpack.h"
#include "userInput.h"
#include "loadSaving.h"

static int32_t add_item_flag = 0;
int8_t game_loop(SDL_Renderer *renderer, SDL_DisplayMode *DM, sBackPack *backpackObj, \
                 int32_t current_key, int32_t luck_val, Item items[100], Npc npcs[100], int8_t loadSuccess){
    if(!loadSuccess){
        char *username = NULL;
        if( userInpName(renderer, DM, &username, "font_lib/Arial.ttf",\
        "挑戰者你好，讓我認識你一下吧，請輸入你的姓名：") == FALSE ){
            return FALSE;
        }
    }
    int8_t quit = 0;
    int32_t dialogX = (DM->w - (DM->w / 5) * 4) / 2;
    int32_t dialogY = DM->h - (DM->h / 4) - 200;
    int32_t dialogW = (DM->w / 5) * 4;
    int32_t dialogH = (DM->h / 4) - 50;
    // sBackPack *backpackObj = SetupBackpack(); // store the item
    // regPrintCallBack(backpackObj, printBackpack);
    // regCmpCallBack(backpackObj, cmp);
    // regFreeCallBack(backpackObj, myFreeFunc);
    // if(debugButton){
        // debugButton = 0;
    // Item item = {.id=10, .name="sword", .picture_file_name="img/sword.png"};
    // AddItemToBackpack(backpackObj, &item);
    // }
    // printBackpackItem(backpackObj);

    Mix_Music *music = NULL;
    PlayMusic("music/party.mp3", music, 24);
    SDL_Event e;
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    // GameState state = STATE_BIRTH;
    int8_t hover[3] = {0};
    int32_t option[3];
    // Item items[100];
    // int32_t total_num_items;
    // Npc npcs[100];
    // int32_t total_num_npcs;
    // char stat_name[100];
    // int32_t luck_val = 0;
    int32_t ret = get_option(pFile, current_key, option);
    if(ret != 0){
        printf("end of story\n");
        return 0;
    }
    // if (get_items(pFile, items, &total_num_items) == 1) {
    //     for (int i = 0; i < total_num_items; i++) {
    //         printf("ID: %d, Name: %s, Picture: %s\n", items[i].id, items[i].name, items[i].picture_file_name);
    //     }
    // } else {
    //     printf("Failed to read items.\n");
    // }
    // if (get_npcs(pFile, npcs, &total_num_npcs) == 1) {
    //     for (int i = 0; i < total_num_npcs; i++) {
    //         printf("ID: %d, Name: %s, Picture: %s, Status: %s, Status Value: %d\n", 
    //             npcs[i].id, 
    //             npcs[i].name, 
    //             npcs[i].picture_file_name, 
    //             npcs[i].status_name[0] == '\0' ? "NULL" : npcs[i].status_name, 
    //             npcs[i].status_val);
    //     }
    // } else {
    //     printf("Failed to read NPCs.\n");
    // }
    // if (get_player_attribute(pFile, stat_name, &luck_val) == 1) {
    //     printf("Stat Name: %s, Stat Value: %d\n", stat_name, luck_val);
    // } else {
    //     printf("Failed to read player attribute.\n");
    // }
    // int8_t finish = 1;
    // extern int8_t finish;
    // SDL_Rect img = {0, 0, DM->w, DM->h};

    SDL_Surface *bg = IMG_Load("img/background.jpg");
   
    if(bg == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return FALSE;
    }
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg);
    // SDL_RenderCopy(renderer, bg_texture, NULL, &img);
    SDL_FreeSurface(bg);
    inEffect = 1;
    outEffect = 0;
    Mix_Chunk *soundEffect = NULL;
    while(!quit){
        // printBackpackItem(backpackObj);
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = 1;
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                // option1 button
                if(x >= 30 && x <= 30 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 1);
                    PlayChunk("music/buttonPress.wav", soundEffect, -1, MIX_MAX_VOLUME, 1);
                    SDL_Delay(150);
                    Mix_HaltChannel(-1);
                    if(soundEffect == NULL) Mix_FreeChunk(soundEffect);
                    outEffect = 1;
                    char backgroundPath[256];
                    if( getBackground(pFile, current_key, backgroundPath) == TRUE ){
                        renderBackground(renderer, DM, backgroundPath);
                    }
                    inEffect = 1;
                    outEffect = 0;
                    current_key = option[0];
                    finish = 1;
                    add_item_flag = 0;
                    SDL_Delay(250);
                }
                // option2 button
                else if(x >= 80 + (DM->w / 3) - 50 && x <= 80 + (DM->w / 3) - 50 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 2);
                    PlayChunk("music/buttonPress.wav", soundEffect, -1, MIX_MAX_VOLUME, 1);
                    SDL_Delay(150);
                    Mix_HaltChannel(-1);
                    if(soundEffect == NULL) Mix_FreeChunk(soundEffect);
                    outEffect = 1;
                    char backgroundPath[256];
                    if( getBackground(pFile, current_key, backgroundPath) == TRUE ){
                        renderBackground(renderer, DM, backgroundPath);
                    }
                    inEffect = 1;
                    outEffect = 0;
                    current_key = option[1];
                    finish = 1;
                    add_item_flag = 0;
                    SDL_Delay(250);
                }
                // option3 button
                else if(x >= 120 + ((DM->w / 3) - 50) * 2 && x <= 120 + ((DM->w / 3) - 50) * 2 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    // handleChoice(&state, 3);
                    PlayChunk("music/buttonPress.wav", soundEffect, -1, MIX_MAX_VOLUME, 1);
                    SDL_Delay(150);
                    Mix_HaltChannel(-1);
                    if(soundEffect == NULL) Mix_FreeChunk(soundEffect);
                    outEffect = 1;
                    char backgroundPath[256];
                    if( getBackground(pFile, current_key, backgroundPath) == TRUE ){
                        renderBackground(renderer, DM, backgroundPath);
                    }
                    inEffect = 1;
                    outEffect = 0;
                    current_key = option[2];
                    finish = 1;
                    add_item_flag = 0;
                    SDL_Delay(250);
                }
                // backpack button
                else if(x > 20 && x < 70 && y > 20 && y < 70){
                    openBackPack = 1;
                }
                // saving button
                else if(x > DM->w - 170 && x < DM->w - 120 && y > 20 && y < 70){
                    // printf("dsafsdafdsf\n");
                    if( save(renderer, DM, current_key, backpackObj, luck_val) == FALSE){
                        return FALSE;
                    }
                }
            }
            else{
                int32_t x, y;
                SDL_GetMouseState(&x, &y);
                if(x >= 30 && x <= 30 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *hover = 1;
                    *(hover + 1) = 0;
                    *(hover + 2) = 0;
                }
                else if(x >= 80 + (DM->w / 3) - 50 && x <= 80 + (DM->w / 3) - 50 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *(hover + 1) = 1;
                    *hover = 0;
                    *(hover + 2) = 0;
                }
                else if(x >= 120 + ((DM->w / 3) - 50) * 2 && x <= 120 + ((DM->w / 3) - 50) * 2 + (DM->w / 3) - 50 && y >= DM->h - (DM->h / 4) + 30 && y <= DM->h - (DM->h / 4) + 30 + (DM->h / 4) - 100){
                    *(hover + 2) = 1;
                    *hover = 0;
                    *(hover + 1) = 0;
                }
                else{
                    for(int32_t i = 0;i < 3;i++) *(hover + i) = 0;
                }
            }
        }

        if( (check_key_format(pFile, current_key) == 0) ){
            int32_t to[3];
            if( get_to(pFile, current_key, to) != 0 ){
                printf("Failed to get the info\n");
                return FALSE;
            }
            if(findItemInBackpack(to[0], backpackObj) == TRUE){
                current_key = to[1];
            }
            else{
                current_key = to[2];
            }
        }

        // printBackpackItem(backpack);
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
        // SDL_RenderCopy(renderer, bg_texture, NULL, &img);
        get_npc_showup(pFile, current_key, npcs, renderer, DM);
        // renderBackground(renderer, DM, "img/background.jpg");
        char backgroundPath[256];
        if( getBackground(pFile, current_key, backgroundPath) == TRUE ){
            renderBackground(renderer, DM, backgroundPath);
        }
        // renderCharacter(renderer, DM, "img/street_fighter.png");
        // renderAvatar(renderer, DM, "img/street_fighter_avatar.jpg");
        // 背包 button
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_Rect backpackRect = {20, 20, 50, 50};
        SDL_RenderFillRect(renderer, &backpackRect);

        // saving button
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_Rect SavingRect = {DM->w - 170, 20, 50, 50};
        SDL_RenderFillRect(renderer, &SavingRect);

        // 對話框
        SDL_SetRenderDrawColor(renderer, 145, 252, 248, 0xFF);
        // printf("%d %d\n",(DM->w / 5) * 3, DM->h);
        SDL_Rect dialogRect = {dialogX, dialogY, dialogW, dialogH};
        SDL_RenderFillRect(renderer, &dialogRect);
        SDL_Color color = {0, 0, 0};
        char *text_name = NULL;
        if( get_text(pFile, current_key, &text_name) == 1 ){
            return FALSE;
        }
        // static int32_t add_item_flag = 0;
        // printf("%d\n", current_key);
        if(add_item_flag==0 && get_add_inventory(pFile, current_key, backpackObj, items) == 0){
            printf("an item added\n");
            add_item_flag = 1;
        }
        if( rendertext_per_sec(renderer, "font_lib/biakai.ttf", \
            text_name, dialogX, \
            dialogY, dialogW, 0, 24, &color) == FALSE){
            return 0;
        }
        // rendertext(renderer, "font_lib/biakai.ttf", text_name, (DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 150, 750, 60, 24, &color);
        SDL_RenderDrawRect(renderer, &dialogRect);
        
        
        // 選擇按鈕
        
        // printf("%d %d %d\n", option[0], option[1], option[2]);
        if( get_option(pFile, current_key, option) == 1 ){
            return FALSE;
        }
        if(option[0] == 0 || option[1] == 0 || option[2] == 0) return FALSE;
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
        get_player_stat(pFile, current_key, &luck_val);
        renderLuckBar(renderer, luck_val, DM);
        // printBackpackItem(backpack);
        if(openBackPack){
            if( backpack_interface(renderer, DM, backpackObj) == FALSE){
                return FALSE;
            }
        }

        SDL_RenderPresent(renderer);
        if(text_name != NULL) free(text_name);

    }
    fclose(pFile);
    cleanBackpack(backpackObj);
    SDL_DestroyTexture(bg_texture);
    Mix_FreeMusic(music);
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
    SDL_Rect luckBar = { DM->w - 100, 20 + (400 - luckValue*4), 50, luckValue*4 };
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