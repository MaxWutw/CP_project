#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h> 
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#endif

int8_t initializeSDL();

#endif