#ifndef _ENDGAME_H_
#define _ENDGAME_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include "constants.h"
#include "utility.h"
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

int8_t winInterface(SDL_Renderer *, SDL_DisplayMode *);
int8_t loseInterface(SDL_Renderer *, SDL_DisplayMode *);
void waveEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t, int32_t);
void blinkingEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t);

#endif