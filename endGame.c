#include "endGame.h"

int8_t winInterface(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    TTF_Font* font = TTF_OpenFont("font_lib/Arial.ttf", 128); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, "You Win", color);
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
    SDL_Rect dstrect = {DM->w / 2 - surface->w / 2, DM->h / 2, surface->w, surface->h};
    blinkingEffect(renderer, texture, &dstrect, 2000, 2);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    return TRUE;
}

int8_t loseInterface(SDL_Renderer *renderer, SDL_DisplayMode *DM){
    SDL_Color color = {0xFF, 0xFF, 0xFF};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
    TTF_Font* font = TTF_OpenFont("font_lib/Arial.ttf", 128); // 使用字體的路徑
    if(font == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return FALSE;
    }
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, "You Lose", color);
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
    SDL_Rect dstrect = {DM->w / 2 - surface->w / 2, DM->h / 2, surface->w, surface->h};
    waveEffect(renderer, texture, &dstrect, 2000, 10, 10);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    return TRUE;
}

void waveEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t amplitude, int32_t frequency){
    int32_t startTick = SDL_GetTicks();
    int32_t elapsed = 0;

    while(elapsed < duration){
        SDL_RenderClear(renderer);
        for(int32_t x = rect->x; x < rect->x + rect->w; ++x){
            double offset = amplitude * sin((double)(frequency * (x - rect->x) + elapsed) * M_PI / 180.0);
            SDL_Rect srcRect = { x - rect->x, 0, 1, rect->h };
            SDL_Rect destRect = { x, rect->y + (int32_t)offset, 1, rect->h };
            SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        elapsed = SDL_GetTicks() - startTick;
    }
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_RenderPresent(renderer);
}

void blinkingEffect(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect, int32_t duration, int32_t frequency){
    int32_t startTick = SDL_GetTicks();
    int32_t elapsed = 0;
    int8_t visible = 1;
    int32_t interval = 1000 / frequency;

    while(elapsed < duration){
        SDL_RenderClear(renderer);
        if(visible){
            SDL_RenderCopy(renderer, texture, NULL, rect);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(interval);
        visible = !visible;
        elapsed = SDL_GetTicks() - startTick;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_RenderPresent(renderer);
}
