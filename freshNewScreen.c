#include "freshNewScreen.h"
#include "constants.h"

int8_t renderCharacter(SDL_Renderer *renderer, SDL_DisplayMode *DM, const char *charPath){
    SDL_Surface *character = IMG_Load(charPath);
    SDL_Rect img = {DM->w / 3, 100, character->w, character->h};
    if(character == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return FALSE;
    }
    SDL_Texture *character_tex = SDL_CreateTextureFromSurface(renderer, character);

    SDL_RenderCopy(renderer, character_tex, NULL, &img);
    SDL_FreeSurface(character);
    SDL_DestroyTexture(character_tex);
    return TRUE;
}

int8_t renderAvatar(SDL_Renderer *renderer, SDL_DisplayMode *DM, const char *charPath){
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0xFF);
    SDL_Rect rect = {(DM->w - (DM->w / 5) * 4) / 2, DM->h - (DM->h / 4) - 150 - 170 - 20, 170, 170};
    SDL_RenderDrawRect(renderer, &rect);
    
    SDL_Surface *avatar = IMG_Load(charPath);
    // printf("%d %d\n", avatar->w, avatar->h);
    SDL_Rect img = {(DM->w - (DM->w / 5) * 4) / 2 + 10, DM->h - (DM->h / 4) - 150 - 150 - 20 - 10, 150, 150};
    if(avatar == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return FALSE;
    }
    SDL_Texture *avatar_tex = SDL_CreateTextureFromSurface(renderer, avatar);
    

    SDL_RenderCopy(renderer, avatar_tex, NULL, &img);
    SDL_FreeSurface(avatar);
    SDL_DestroyTexture(avatar_tex);
    return TRUE;
}