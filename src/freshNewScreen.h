#ifndef _FRESHNEWSCREEN_H_
#define _FRESHNEWSCREEN_H_
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <wchar.h>
#include <locale.h>
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

int8_t renderBackground(SDL_Renderer *, SDL_DisplayMode *, const char *);
int8_t renderCharacter(SDL_Renderer *, SDL_DisplayMode *, const char *);
int8_t renderCharacter2(SDL_Renderer *renderer, SDL_DisplayMode *DM, const char *charPath, int x, int y, int width, int height);
int8_t renderAvatar(SDL_Renderer *, SDL_DisplayMode *, const char *);
void fadeEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t);
void slideEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t);
void zoomEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t);
void rotateEffect(SDL_Renderer *, SDL_Texture *, SDL_Rect *, int32_t, int32_t);

extern int8_t inEffect;
extern int8_t outEffect;

#endif