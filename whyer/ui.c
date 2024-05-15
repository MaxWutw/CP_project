#include <SDL.h>
#include <SDL_ttf.h>
#include "ui.h"

void renderText(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h) {
    TTF_Font* font = TTF_OpenFont("assets/Arial.ttf", 24); // 使用字體的路徑
    if (font == NULL) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        return;
    }
    SDL_Color color = { 0, 0, 0 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstrect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void renderChoices(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_Rect choiceRect1 = { 150, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect1);
    renderText(renderer, "rich", 170, 460, 60, 30);

    SDL_Rect choiceRect2 = { 350, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect2);
    renderText(renderer, "poor", 370, 460, 60, 30);

    SDL_Rect choiceRect3 = { 550, 450, 100, 50 };
    SDL_RenderDrawRect(renderer, &choiceRect3);
    renderText(renderer, "orphan", 570, 460, 60, 30);
}

void renderLuckBar(SDL_Renderer* renderer, int luckValue) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xA5, 0x00, 0xFF);
    SDL_Rect luckBarOutline = { 700, 20, 20, 100 };
    SDL_RenderDrawRect(renderer, &luckBarOutline);
    SDL_Rect luckBar = { 700, 20 + (100 - luckValue), 20, luckValue };
    SDL_RenderFillRect(renderer, &luckBar);
}
