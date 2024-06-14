#ifndef _LOADSAVING_H_
#define _LOADSAVING_H_
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
#include "userInput.h"
#include "player_stats.h"
#include "backpack.h"
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

int8_t save(SDL_Renderer *, SDL_DisplayMode *, int32_t, sBackPack *);
int8_t load(SDL_Renderer *, SDL_DisplayMode *);
int8_t saveData(SDL_Renderer *, SDL_DisplayMode *, int32_t, sBackPack *);
int8_t save2json(sBackPack *, int32_t, char *);
int8_t loadFromJson(char [512][512]);
int8_t process_file(const char *, char [512][512]);


#endif