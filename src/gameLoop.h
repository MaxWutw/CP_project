#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "backpack.h"
#include "endGame.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#include <SDL_ttf.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#endif

typedef enum {
    STATE_BIRTH,
    STATE_CHILDHOOD,
    STATE_ADULTHOOD,
    STATE_OLDAGE,
    STATE_END
} GameState;

int8_t game_loop(SDL_Renderer *, SDL_DisplayMode *, sBackPack *, int32_t, int32_t, Item [100], Npc [100], int8_t);
void renderChoices(SDL_Renderer*, const char*, const char*, const char*, SDL_DisplayMode *, int8_t *);
void renderLuckBar(SDL_Renderer*, int, SDL_DisplayMode *);
void handleChoice(GameState*, int);
const char* getDialogText(GameState);
int getLuckValue(GameState);
int8_t howToPlay(SDL_Renderer *, SDL_DisplayMode *, FILE *);

#endif