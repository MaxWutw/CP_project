#include "freshNewScreen.h"
#include "constants.h"

int8_t inEffect = 0;
int8_t outEffect = 0;
int32_t effectChoice = 0;

int8_t renderBackground(SDL_Renderer *renderer, SDL_DisplayMode *DM, const char *bgPath){
    SDL_Rect img = {0, 0, DM->w, DM->h};
    SDL_Surface *bg = IMG_Load(bgPath);
    if(bg == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return FALSE;
    }
    effectChoice %= 4;
    SDL_Texture *bg_texture = SDL_CreateTextureFromSurface(renderer, bg);
    if(inEffect){
        if(effectChoice == 0) fadeEffect(renderer, bg_texture, &img, 1250, 255); // fade in
        else if(effectChoice == 1) slideEffect(renderer, bg_texture, &img, 1250, 0); // left to right
        else if(effectChoice == 2) zoomEffect(renderer, bg_texture, &img, 1250, 1);
        else if(effectChoice == 3) rotateEffect(renderer, bg_texture, &img, 1250, 1);
        inEffect = 0;
    }
    else if(outEffect){
        if(effectChoice == 0) fadeEffect(renderer, bg_texture, &img, 1250, 0); // fade out
        else if(effectChoice == 1) slideEffect(renderer, bg_texture, &img, 1250, 1); // right to left
        else if(effectChoice == 2) zoomEffect(renderer, bg_texture, &img, 1250, 0);
        else if(effectChoice == 3) rotateEffect(renderer, bg_texture, &img, 1250, 0);
        outEffect = 0;
        effectChoice++;
    }

    SDL_RenderCopy(renderer, bg_texture, NULL, &img);
    SDL_FreeSurface(bg);

    return TRUE;
}

int8_t renderCharacter(SDL_Renderer *renderer, SDL_DisplayMode *DM, const char *charPath){
    SDL_Surface *character = IMG_Load(charPath);
    if(character == NULL){
        printf("Error Read Image: %s\n", SDL_GetError());
        return FALSE;
    }
    SDL_Rect img = {DM->w / 3, 100, character->w, character->h};
    SDL_Texture *character_tex = SDL_CreateTextureFromSurface(renderer, character);

    // fadeEffect(renderer, character_tex, &img, 1250, 0);
    // if(inEffect) fadeEffect(renderer, character_tex, &img, 1250, 0);
    // else if(outEffect) fadeEffect(renderer, character_tex, &img, 1250, 255);

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

void fadeEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t fadeIn){
    int32_t alpha = fadeIn ? 0 : 255; // fade in or fade out
    int32_t step = 255 / (duration / 16); // assuming 60 FPS, so approximately 16 ms per frame
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    while((fadeIn && alpha < 255) || (!fadeIn && alpha > 0)){
        SDL_SetTextureAlphaMod(texture, alpha);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        alpha += fadeIn ? step : -step;
    }
    SDL_SetTextureAlphaMod(texture, 255);
}

void slideEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t direction){
    int step = rect->w / (duration / 16); // assuming 60 FPS, so approximately 16 ms per frame
    int startX = direction == 0 ? -rect->w : rect->w;
    int endX = rect->x;

    for(int x = startX; (direction == 0 ? x < endX : x > endX); x += (direction == 0 ? step : -step)){
        SDL_RenderClear(renderer);
        SDL_Rect tempRect = {x, rect->y, rect->w, rect->h};
        SDL_RenderCopy(renderer, texture, NULL, &tempRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_RenderPresent(renderer);
}

void zoomEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t zoomIn){
    int step = rect->w / (duration / 16); // assuming 60 FPS, so approximately 16 ms per frame
    int startW = zoomIn ? 0 : rect->w;
    int endW = rect->w;
    int startH = zoomIn ? 0 : rect->h;
    int endH = rect->h;

    for(int w = startW, h = startH; (zoomIn ? w < endW && h < endH : w > 0 && h > 0); 
         w += (zoomIn ? step : -step), h += (zoomIn ? step : -step)){
        SDL_RenderClear(renderer);
        SDL_Rect tempRect = {rect->x + (rect->w - w) / 2, rect->y + (rect->h - h) / 2, w, h};
        SDL_RenderCopy(renderer, texture, NULL, &tempRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_RenderPresent(renderer);
}

void rotateEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t clockwise){
    int angle = clockwise ? 0 : 360;
    int step = 360 / (duration / 16); // assuming 60 FPS, so approximately 16 ms per frame

    while((clockwise && angle < 360) || (!clockwise && angle > 0)){
        SDL_RenderClear(renderer);
        SDL_RenderCopyEx(renderer, texture, NULL, rect, angle, NULL, SDL_FLIP_NONE);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        angle += (clockwise ? step : -step);
    }
    SDL_RenderCopyEx(renderer, texture, NULL, rect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(renderer);
}