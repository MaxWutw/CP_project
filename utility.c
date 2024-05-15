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

int8_t setup(const char* program_name, SDL_Window **win, SDL_Renderer **renderer, \
            SDL_Surface **surface, SDL_Texture **texture, TTF_Font **TitleFont, SDL_DisplayMode *DM){
    SDL_GetCurrentDisplayMode(0, DM);
    *win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM->w, DM->h, SDL_WINDOW_RESIZABLE);
    printf("window width: %d \nwindow height: %d\n", DM->w, DM->h);
    SDL_ShowWindow(*win);
    if(*win == NULL){
        fprintf(stderr, "Error: Window could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    // Renderer
    *renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(*renderer == NULL){
        fprintf(stderr, "Error: Renderer could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(*win);
        return FALSE;
    }

    // Font
    *TitleFont = TTF_OpenFont("font_lib/Martyric_PersonalUse.ttf", 108);
    if (*TitleFont == NULL) {
        fprintf(stderr, "Error: Failed to load font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
        DestoryAll_and_Quit(*TitleFont, *texture, *renderer, *win);
        return FALSE;
    }
    return TRUE;
}

int8_t process_input(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            return FALSE;
        }
        else if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_ESCAPE){
                return FALSE;
            }
            else if(event.key.keysym.sym == SDLK_UP){
                selected_item = (selected_item - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            }
            else if(event.key.keysym.sym == SDLK_DOWN){
                selected_item = (selected_item + 1) % MENU_ITEM_COUNT;
            }
            else if(event.key.keysym.sym == SDLK_RETURN){
                switch(selected_item) {
                    case 0:
                        printf("Start Game\n");
                        break;
                    case 1:
                        printf("Author\n");
                        break;
                    case 2:
                        printf("How to Play\n");
                        break;
                }
            }
        }
    }
    return TRUE;
}

int8_t update_title_screen(uint32_t *last_frame_time, SDL_Rect *textRect, int32_t *inc, int32_t *base_y){
    // int32_t time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - *last_frame_time);
    // if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
    //     SDL_Delay(time_to_wait);
    // }
    // uint32_t current_time = SDL_GetTicks();
    // uint32_t del_time = (SDL_GetTicks() - *last_frame_time) / 1000.0;
    // printf("%d\n", *last_frame_time);
    // *last_frame_time = current_time;
    // int32_t move = *velocity_y * del_time;
    textRect->y += *inc; 
    // printf("%d\n", textRect->y);
    if(textRect->y >= *base_y + 50 || textRect->y <= *base_y - 50){
        *inc = -*inc;
    }
    
    return TRUE;
}

int8_t render_title_screen(SDL_Window **win, SDL_Renderer **renderer, \
            SDL_Surface **surface, SDL_Texture **texture, TTF_Font **TitleFont, SDL_DisplayMode *DM, SDL_Rect *textRect){

    // render menu
    SDL_Color menu_color = {255, 255, 255};
    TTF_Font *menu_font = TTF_OpenFont("font_lib/Arial.ttf", 36);
    if(menu_font == NULL) {
        fprintf(stderr, "Error: Failed to load menu font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
        DestoryAll_and_Quit(*TitleFont, *texture, *renderer, *win);
        return FALSE;
    }
    const char* menu_items[MENU_ITEM_COUNT] = {
        "Start Game",
        "Author",
        "How to Play"
    };

    for(int i = 0; i < MENU_ITEM_COUNT; i++) {
        SDL_Surface *menu_surface = TTF_RenderText_Blended(menu_font, menu_items[i], menu_color);
        SDL_Texture *menu_texture = SDL_CreateTextureFromSurface(*renderer, menu_surface);
        SDL_Rect menu_rect;
        SDL_QueryTexture(menu_texture, NULL, NULL, &menu_rect.w, &menu_rect.h);
        menu_rect.x = ((DM->w - menu_rect.w) / 2);
        menu_rect.y = ((DM->h - menu_rect.h) / 2) + i * 50;
        SDL_RenderCopy(*renderer, menu_texture, NULL, &menu_rect);
        SDL_FreeSurface(menu_surface);
        SDL_DestroyTexture(menu_texture);
    }

    TTF_CloseFont(menu_font);
    SDL_RenderCopy(*renderer, *texture, NULL, textRect);
    // clears the screen
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, *texture, NULL, textRect);
    SDL_RenderPresent(*renderer);

    return TRUE;
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