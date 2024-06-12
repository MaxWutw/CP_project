#ifndef _LOADSAVING_H_
#define _LOADSAVING_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
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

int8_t save(SDL_Renderer *, SDL_DisplayMode *, int32_t rrent_key);
int8_t load(SDL_Renderer *, SDL_DisplayMode *);

#endif