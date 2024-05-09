#include "utility.h"
#include "constants.h"


/* Initialize SDL, adding it to the front of the code*/
int8_t initializeSDL(){
    /*
     #define SDL_INIT_EVERYTHING ( \
                SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | \
                SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER | SDL_INIT_SENSOR \
            )
     */
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return FALSE;
    }

    if(TTF_Init() == -1){
        printf("Error initializing TTF: %s\n", SDL_GetError());
        return FALSE;
    }

    int32_t imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        printf("Error initializing Image: %s\n", SDL_GetError());
        return FALSE;
    }
    return TRUE;
}

int8_t setup(const char* program_name, SDL_Window *win, SDL_Renderer *renderer, \
            SDL_Surface *surface, SDL_Texture *texture, TTF_Font *TitleFont, SDL_DisplayMode *DM){
    SDL_GetCurrentDisplayMode(0, DM);
    win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM->w, DM->h, SDL_WINDOW_RESIZABLE);
    printf("window width: %d \nwindow height: %d\n", DM->w, DM->h);
    SDL_ShowWindow(win);
    if(win == NULL){
        fprintf(stderr, "Error: Window could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    // Renderer
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL){
        fprintf(stderr, "Error: Renderer could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        return FALSE;
    }

    // Font
    TitleFont = TTF_OpenFont("font_lib/Martyric_PersonalUse.ttf", 48);
    if (TitleFont == NULL) {
        fprintf(stderr, "Error: Failed to load font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
        DestoryAll_and_Quit(TitleFont, texture, renderer, win);
        return FALSE;
    }
    return TRUE;
}

int8_t process_input(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT){
        return FALSE;
    }
    else if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE){
            return FALSE;
        }
    }
    return TRUE;
}

int8_t update_title_screen(float *last_frame_time){
    // int32_t del_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
    // last_frame_time = SDL_GetTicks();
    
    
}

int8_t render_title_screen(SDL_Window *win, SDL_Renderer *renderer, \
            SDL_Surface *surface, SDL_Texture *texture, TTF_Font *TitleFont){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
}

void DestoryAll_and_Quit(TTF_Font* font, SDL_Texture *texture, SDL_Renderer *renderer, \
                        SDL_Window *win){
    if(font != NULL) TTF_CloseFont(font);
    if(texture != NULL) SDL_DestroyTexture(texture);
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(win != NULL) SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}