#ifndef _MUSICUTIL_C_
#define _MUSICUTIL_C_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "constants.h"
#ifdef __linux__
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#elif __APPLE__
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif

// 給像是背景音樂這種比較長的音樂
// free is your own businuss
// Mix_FreeMusic()
// volume: 0 ~ 128
int8_t PlayMusic(const char *, Mix_Music *, int32_t);

// 短暫的音效
// free is your own businuss
// Mix_FreeChunk()
// volume: 0 ~ 128
int8_t PlayChunk(const char *, Mix_Chunk *, int32_t, int32_t, int32_t);

#endif