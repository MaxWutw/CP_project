#ifndef _BACKPACK_H_
#define _BACKPACK_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
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

int8_t backpack_interface(SDL_Renderer *, SDL_DisplayMode *);
int32_t calPersonDeposit();
char* PersonCurStatus();
int8_t AddItemToBackpack();

#endif