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

    int32_t flags = MIX_INIT_OGG | MIX_INIT_MP3;
    int32_t initted = Mix_Init(flags);
    if((initted & flags) != flags){
        printf("Mix_Init: Failed to init required ogg, mod and mp3 support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        // handle error
        return FALSE;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("Error initializing Mixer: %s\n", Mix_GetError());
        return FALSE;
    }

    return TRUE;
}

int8_t setup(const char* program_name, SDL_Window **win, SDL_Renderer **renderer, SDL_DisplayMode *DM){
    SDL_GetCurrentDisplayMode(0, DM);
    // DM->h -= 100;
    *win = SDL_CreateWindow(program_name , SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DM->w, DM->h, SDL_WINDOW_RESIZABLE);
    printf("window width: %d \nwindow height: %d\n", DM->w, DM->h);
    SDL_ShowWindow(*win);
    // if(*win == NULL){
    //     printf("error!!!!!!!!!!!!!!!\n");
    //     fprintf(stderr, "Error: Window could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
    //     return 0;
    // }
    // Renderer
    *renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // if(*renderer == NULL){
    //     fprintf(stderr, "Error: Renderer could not be created! Program Terminated!! \nSDL_Error: %s\n", SDL_GetError());
    //     SDL_DestroyWindow(*win);
    //     return FALSE;
    // }

    return TRUE;
}

int8_t process_input(int8_t *selected_item, SDL_Rect *fillRect1, SDL_Rect *fillRect2, SDL_Rect *fillRect3, SDL_Renderer *renderer, int32_t *title_status){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        if(event.type == SDL_QUIT){
            return FALSE;
        }
        else if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_ESCAPE){
                return FALSE;
            }
            else if(event.key.keysym.sym == SDLK_UP){
                *selected_item = (*selected_item - 1 + MENU_ITEM_COUNT) % MENU_ITEM_COUNT;
            }
            else if(event.key.keysym.sym == SDLK_DOWN){
                *selected_item = (*selected_item + 1) % MENU_ITEM_COUNT;
            }
            else if(event.key.keysym.sym == SDLK_RETURN){
                switch(*selected_item) {
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
        else if(event.type == SDL_MOUSEBUTTONDOWN){
            if(mouseX > fillRect1->x && mouseX < fillRect1->x + fillRect1->w && \
                mouseY > fillRect1->y && mouseY < fillRect1->y + fillRect1->h){
                *title_status = 1;
                return FALSE;
            }
            if(mouseX > fillRect2->x && mouseX < fillRect2->x + fillRect2->w && \
                mouseY > fillRect2->y && mouseY < fillRect2->y + fillRect2->h) {
                *title_status = 2;
                return FALSE;
            }
            if(mouseX > fillRect3->x && mouseX < fillRect3->x + fillRect3->w && \
                mouseY > fillRect3->y && mouseY < fillRect3->y + fillRect3->h){
                *title_status = 3;
                return FALSE;
            }
        }
    }

    SDL_Color color_black = {0, 0, 0};

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if(mouseX > fillRect1->x && mouseX < fillRect1->x + fillRect1->w && \
        mouseY > fillRect1->y && mouseY < fillRect1->y + fillRect1->h){
        SDL_SetRenderDrawColor(renderer, 154, 154, 154, 0xFF);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    SDL_RenderFillRect(renderer, fillRect1);
    rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "Start Game", fillRect1->x, fillRect1->y, fillRect1->w, fillRect1->h, 48, &color_black);


    if(mouseX > fillRect2->x && mouseX < fillRect2->x + fillRect2->w && \
        mouseY > fillRect2->y && mouseY < fillRect2->y + fillRect2->h) {
        SDL_SetRenderDrawColor(renderer, 154, 154, 154, 0xFF);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    SDL_RenderFillRect(renderer, fillRect2);
    rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "How To Play", fillRect2->x, fillRect2->y, fillRect2->w, fillRect2->h, 40, &color_black);

    if(mouseX > fillRect3->x && mouseX < fillRect3->x + fillRect3->w && \
        mouseY > fillRect3->y && mouseY < fillRect3->y + fillRect3->h){
        SDL_SetRenderDrawColor(renderer, 154, 154, 154, 0xFF);
    }
    else{
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    }
    SDL_RenderFillRect(renderer, fillRect3);
    rendertext(renderer, "font_lib/Martyric_PersonalUse.ttf", "Author", fillRect3->x, fillRect3->y, fillRect3->w, fillRect3->h, 48, &color_black);


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
    if(textRect->y >= *base_y + 20 || textRect->y <= *base_y - 20){
        *inc = -*inc;
    }
    
    return TRUE;
}

int8_t render_title_screen(SDL_Window **win, SDL_Renderer **renderer, SDL_DisplayMode *DM, SDL_Rect *textRect){
    // render menu
    // SDL_Color menu_color = {255, 255, 255};
    // TTF_Font *menu_font = TTF_OpenFont("font_lib/Arial.ttf", 36);
    // if(menu_font == NULL) {
    //     fprintf(stderr, "Error: Failed to load menu font! Program Terminated!! \nSDL_Error: %s\n", TTF_GetError());
    //     DestoryAll_and_Quit(*renderer, *win);
    //     return FALSE;
    // }
    // const char* menu_items[MENU_ITEM_COUNT] = {
    //     "Start Game",
    //     "Author",
    //     "How to Play"
    // };

    // TTF_CloseFont(menu_font);
    // SDL_RenderCopy(*renderer, *texture, NULL, textRect);
    // clears the screen
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);
    SDL_RenderClear(*renderer);
    // SDL_RenderCopy(*renderer, *texture, NULL, textRect);
    SDL_RenderPresent(*renderer);

    return TRUE;
}

void DestoryAll_and_Quit(SDL_Renderer *renderer, SDL_Window *win){
    if(renderer != NULL) SDL_DestroyRenderer(renderer);
    if(win != NULL) SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
}

// int8_t rendertext(SDL_Renderer* renderer, const char* font_path, const char* text, int32_t x, int32_t y, int32_t w, int32_t h, int32_t fontSize, SDL_Color *color){
//     TTF_Font* font = TTF_OpenFont(font_path, fontSize);
//     if(font == NULL){
//         printf("TTF_OpenFont: %s\n", TTF_GetError());
//         return FALSE;
//     }

//     char* text_copy = strdup(text);
//     char* line_start = text_copy;
//     int32_t y_offset = 0;

//     while(*line_start){
//         int32_t line_width = 0;
//         char* ptr = line_start;
//         while(*ptr){
//             int char_width;
//             TTF_SizeUTF8(font, ptr, &char_width, NULL);
//             line_width += char_width;
//             if(line_width > w){
//                 break;
//             }
//             ptr++;
//         }
//         char saved_char = *ptr;
//         printf("%c\n", saved_char);
//         *ptr = '\0';

//         SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, *color);
//         if(surface == NULL){
//             printf("TTF_RenderUTF8_Solid: %s\n", SDL_GetError());
//             TTF_CloseFont(font);
//             return FALSE;
//         }

//         SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
//         if(texture == NULL){
//             printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
//             SDL_FreeSurface(surface);
//             TTF_CloseFont(font);
//             return FALSE;
//         }
//         SDL_Rect dstrect = {x, y + y_offset, surface->w, surface->h};
//         if(SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0){
//             printf("SDL_RenderCopy: %s\n", SDL_GetError());
//             SDL_FreeSurface(surface);
//             SDL_DestroyTexture(texture);
//             TTF_CloseFont(font);
//         }
//         y_offset += surface->h;
//         SDL_FreeSurface(surface);
//         SDL_DestroyTexture(texture);

//         if(saved_char == '\0'){
//             break;
//         }
//         *ptr = saved_char;
//         line_start = ptr + 1;
//     }

//     TTF_CloseFont(font);
//     free(text_copy);

//     return TRUE;
// }

int8_t rendertext(SDL_Renderer* renderer, const char* font_path, const char* text, int32_t x, int32_t y, int32_t w, int32_t h, int32_t fontSize, SDL_Color *color){
    TTF_Font* font = TTF_OpenFont(font_path, fontSize); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, *color);
    if(surface == NULL){
        printf("TTF_RenderUTF8_Solid: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        return FALSE;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL){
        printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return FALSE;
    }
    SDL_Rect dstrect = {x, y, surface->w, surface->h};
    if(SDL_RenderCopy(renderer, texture, NULL, &dstrect) != 0){
        printf("SDL_RenderCopy: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);

    return TRUE;
}

// render text per sec
int8_t rendertext_per_sec(SDL_Renderer* renderer, const char* font_path, const char* text, int x, int y, int w, int h, int fontSize, SDL_Color *color){
    setlocale(LC_ALL, "");
    TTF_Font* font = TTF_OpenFont(font_path, fontSize); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }
    // SDL_Color color = {0, 0, 0};
    // SDL_Surface* surface = TTF_RenderText_Blended(font, text, *color);
    SDL_Surface *surface;
    SDL_Texture* texture;
    int32_t cur_x = x;
    const char *it = text;
    // extern int8_t finish;
    Mix_Chunk *sound = NULL;
    if(finish){
        PlayChunk("music/keyboard_typing.mp3", sound, -1, 128);
    }
    while(*it && finish){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_SPACE){
                    finish = 0;
                    Mix_HaltChannel(-1);
                    if(sound != NULL) Mix_FreeChunk(sound);
                    break;
                }
                // Enter pressed
                // else if(event.key.keysym.sym == SDLK_RETURN){

                // }
            }
            else if(event.type == SDL_QUIT){
                Mix_HaltChannel(-1);
                if(sound != NULL) Mix_FreeChunk(sound);
                return FALSE;
            }
        }
        wchar_t wc;
        int32_t leng = mbtowc(&wc, it, MB_CUR_MAX);
        if(leng < 0){
            perror("mbtwoc");
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
            Mix_HaltChannel(-1);
            if(sound != NULL) Mix_FreeChunk(sound);
            return FALSE;
        }
        char utf8_char[MB_CUR_MAX + 1];
        memcpy(utf8_char, it, leng);
        utf8_char[leng] = '\0';

        surface = TTF_RenderUTF8_Solid(font, utf8_char, *color);
        if(surface == NULL){
            fprintf(stderr, "TTF_RenderUTF8_Solid Error: %s\n", TTF_GetError());
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
            Mix_HaltChannel(-1);
            if(sound != NULL) Mix_FreeChunk(sound);
            return FALSE;
        }
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        int32_t tmp_increase = surface->w;
        if(texture == NULL){
            fprintf(stderr, "TTF_RenderUTF8_Solid Error: %s\n", TTF_GetError());
            SDL_DestroyTexture(texture);
            TTF_CloseFont(font);
            Mix_HaltChannel(-1);
            if(sound != NULL) Mix_FreeChunk(sound);
            return FALSE;
        }

        SDL_Rect dstrect = {cur_x, y, tmp_increase, surface->h};
        SDL_FreeSurface(surface);
        cur_x += tmp_increase;
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        SDL_DestroyTexture(texture);
        it += leng;
        // printf("%d\n", cur_x);
        if(cur_x >= (x + w) - 20){
            cur_x = x;
            y += surface->h;
        }
    }
    // Mix_Pause(-1);
    if(finish){
        Mix_HaltChannel(-1);
    }
    if(sound != NULL) Mix_FreeChunk(sound);
    finish = 0;
    rendertext(renderer, "font_lib/biakai.ttf", text, x, y, w, h, fontSize, color);
    // SDL_RenderPresent(renderer);
    TTF_CloseFont(font);

    return TRUE;
}