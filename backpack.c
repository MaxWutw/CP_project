#include "backpack.h"
#include "utility.h"
#include "constants.h"

int8_t backpack_interface(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    SDL_SetRenderDrawColor(renderer, 91, 245, 173, 0xFF);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    // SDL_Rect rect = {};
    // SDL_RenderFillRect(renderer, &rect);

    return TRUE;
}