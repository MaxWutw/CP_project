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
        return -1;
    }

    if(TTF_Init() == -1){
        printf("Error initializing TTF: %s\n", SDL_GetError());
        return -1;
    }

    int32_t imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags)){
        printf("Error initializing Image: %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

// int8_t process_input(){
//     // SDL_Event event;
//     // SDL_PollEvent(&event);
//     // if(event.type == SDL_QUIT){
//     //     game_is_running = FALSE;
//     // }
//     // else if(event.type == SDL_KEYDOWN){
//     //     if(event.key.keysym.sym == SDLK_ESCAPE){
//     //         game_is_running = FALSE;
//     //     }
//     // }
// }

// int8_t update_screen(){
    
// }

// int8_t render_screen(){

// }

// void DestoryAll(){

// }