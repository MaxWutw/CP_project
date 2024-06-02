#ifndef _UTILITY_H_
#define _UTILITY_H_
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

int8_t initializeSDL();
int8_t setup(const char* , SDL_Window **, SDL_Renderer **, SDL_DisplayMode *);
int8_t basic_background();
int8_t process_input(int8_t *, SDL_Rect *, SDL_Rect *, SDL_Rect *, SDL_Renderer *, int32_t *);
int8_t update_title_screen(uint32_t *, SDL_Rect *, int32_t *, int32_t *);
int8_t render_title_screen(SDL_Window **, SDL_Renderer **, SDL_DisplayMode *, SDL_Rect *);
void DestoryAll_and_Quit(SDL_Renderer *, SDL_Window *);
int8_t rendertext(SDL_Renderer* , const char*, const char* , int32_t, int32_t, int32_t, int32_t, int32_t, SDL_Color *);
int8_t rendertext_per_sec(SDL_Renderer*, const char*, const char*, int32_t , int32_t, int32_t, int32_t, int32_t, SDL_Color *);

#endif