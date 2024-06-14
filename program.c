#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "toml_parse.h"
#include "utility.h"
#include "constants.h"
#include "gameLoop.h"
#include "musicUtil.h"
#include "loadSaving.h"
#include "backpack.h"
#include "player_stats.h"
#include "toml_parse_item.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif

// 看這邊！

// 作法：
// make
// ./program
// 你可以把滑鼠游標滑過每個按鍵，會有 hover 的效果
// 如果按下 Start Game ，我的 title_status 會變成 1 同時 title_is_running 會變成 FALSE ，也就是說我的 while 迴圈會跳出來，
// 你可以在 while(title_is_running) 後面接上如果 if(title_status == 1) 然後接到遊戲開始，
// 歐還有我的 title 是全螢幕的

int8_t title_is_running = 1;
int8_t selected_item = 0;
int main(int argc, char *argv[]){
    FILE *pFile = NULL;
    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    fclose(pFile);
    // atexit(DestoryAll);
    if( (title_is_running = initializeSDL()) == 0){
        fprintf(stderr, "Error: Failed to initialize SDL! Program Termainated!!\nSDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // get name
    const char *program_name = NULL;
    if((program_name = "test") == NULL){
        fprintf(stderr, "Error: Failed to get the name from get_name function! Program Terminated!!\n");
        return 0;
    }
    printf("%s\n", program_name);
    // setup 
    SDL_Window *win = NULL;
    SDL_DisplayMode DM;
    SDL_Renderer *renderer = NULL;
    setup(program_name, &win, &renderer, &DM);
    uint32_t last_frame_time = 0.0;
    SDL_Rect textRect;
    SDL_Color color_white = {255, 255, 255};
    // SDL_Color color_black = {0, 0, 0};
    const char *TitleText = "Life Simulator";
    // some intiaize
    
    textRect.w = 500;
    textRect.h = 200;
    textRect.x = ((DM.w - textRect.w) / 2) - 300;
    textRect.y = ((DM.h - textRect.h) / 2) - 250;
    int32_t inc = 1, base_y = textRect.y;

    sBackPack *backpackObj = SetupBackpack(); // store the item
    regPrintCallBack(backpackObj, printBackpack);
    regCmpCallBack(backpackObj, cmp);
    regFreeCallBack(backpackObj, myFreeFunc);

    int32_t title_status = 0;
    Mix_Music *music = NULL;
    PlayMusic("music/music_theme.mp3", music, 64);
    // game setup

    if(((pFile = fopen("script.toml", "r")) == NULL)){
        fprintf(stderr, "Error: Failed to open the script! Program Terminated!!\n");
        return 0;
    }
    int32_t current_key = START;
    Item items[100];
    int32_t total_num_items;
    Npc npcs[100];
    int32_t total_num_npcs;
    char stat_name[100];
    int32_t luck_val = 0;
    if (get_items(pFile, items, &total_num_items) == 1) {
        for (int i = 0; i < total_num_items; i++) {
            printf("ID: %d, Name: %s, Picture: %s\n", items[i].id, items[i].name, items[i].picture_file_name);
        }
    } else {
        printf("Failed to read items.\n");
    }
    if (get_npcs(pFile, npcs, &total_num_npcs) == 1) {
        for (int i = 0; i < total_num_npcs; i++) {
            printf("ID: %d, Name: %s, Picture: %s, Status: %s, Status Value: %d\n", 
                npcs[i].id, 
                npcs[i].name, 
                npcs[i].picture_file_name, 
                npcs[i].status_name[0] == '\0' ? "NULL" : npcs[i].status_name, 
                npcs[i].status_val);
        }
    } else {
        printf("Failed to read NPCs.\n");
    }
    if (get_player_attribute(pFile, stat_name, &luck_val) == 1) {
        printf("Stat Name: %s, Stat Value: %d\n", stat_name, luck_val);
    } else {
        printf("Failed to read player attribute.\n");
    }

    // game setup end
    while(title_is_running){
        
        update_title_screen(&last_frame_time, &textRect, &inc, &base_y);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", TitleText, textRect.x, textRect.y, textRect.w + DM.w, textRect.h, 108, &color_white);
        SDL_Rect fillRect1 = {(DM.w - 200) / 2, (DM.h - 50) / 2, 200, 100};
        SDL_Rect fillRect2 = {(DM.w - 200) / 2, (DM.h + 200) / 2, 200, 100};
        SDL_Rect fillRect3 = {(DM.w - 200) / 2, (DM.h + 450) / 2, 200, 100};

        title_is_running = process_input(&selected_item, &fillRect1, &fillRect2, &fillRect3, renderer, &title_status);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);

        // title_status = 1; // dubug
        // break; //debug
    }
    while(!Mix_FadeOutMusic(3000) && Mix_PlayingMusic()) {
        // wait for any fades to complete
        SDL_Delay(100);
    }
    if(music != NULL) Mix_FreeMusic(music);

    // if(title_status == 1) game_loop(renderer, &DM);
    if(title_status == 1){
        int32_t alpha = 255;
        while(alpha > 0){
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);

            rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", TitleText, textRect.x, textRect.y, textRect.w + DM.w, textRect.h, 108, &color_white);

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
            SDL_RenderFillRect(renderer, NULL);
            SDL_RenderPresent(renderer);

            SDL_Delay(1000 / 60);
            alpha -= 5;
        }
        game_loop(renderer, &DM, backpackObj, current_key, luck_val, items, npcs, 0);
    }
    else if(title_status == 3){
        if( load(renderer, &DM, &current_key, &luck_val, items, npcs, backpackObj) == FALSE ){
            return FALSE;
        }
        game_loop(renderer, &DM, backpackObj, current_key, luck_val, items, npcs, 1);
    }

    // close ttf
    // TTF_CloseFont(TitleFont);

    // destroy texture
    // SDL_DestroyTexture(texture);

    // destroy renderer
    // Mix_FreeMusic(music);
    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);

    // destory window
    SDL_DestroyWindow(win);

    SDL_Quit();
    // DestoryAll_and_Quit(TitleFont, texture, renderer, win);

    return 0;
}