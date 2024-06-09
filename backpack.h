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

typedef struct _sListParam{
    int32_t size;
    void (*myfree)(void *);
    // return 0 for equal
    int8_t (*cmp)(const void *, const void *);
}sListParam;

typedef struct _sListNode{
    void *pData;
    struct _sListNode *pNext;
}sListNode;

typedef struct _sBackPack{
    struct _sListParam *pParam;
    struct _sListNode *pHead;
    struct _sListNode *pTail;
}sBackPack;

int8_t backpack_interface(SDL_Renderer *, SDL_DisplayMode *);
int32_t calPersonDeposit();
char* PersonCurStatus();
int8_t AddItemToBackpack(sBackPack *backpack, void *inpData);
int8_t RemoveItemFromBackpack(sBackPack *bakcpack, void *inpData);
void regCmpCallBack(sBackPack *backpack, int8_t (*cmp)(const void *, const void *));
void regFreeCallBack(sBackPack *backpack, void (*myfree)(void *));

#endif