#ifndef _USERINPUT_H_
#define _USERINPUT_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "constants.h"
#include "utility.h"
#include "player_stats.h"
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

int8_t  userInpName(SDL_Renderer *, SDL_DisplayMode *, char **text, const char*, const char *);

#endif