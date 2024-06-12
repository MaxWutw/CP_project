#include "backpack.h"
#include "utility.h"
#include "constants.h"

static int8_t __updateBackpack(SDL_Renderer *, sBackPack *, int32_t , int32_t , int32_t, int32_t);
int8_t backpack_interface(SDL_Renderer *renderer, SDL_DisplayMode *DM, sBackPack *backpack){
    int8_t quit = 0;
    while(!quit){
        // SDL_SetRenderDrawColor(renderer, 91, 245, 173, 0xFF);
        // SDL_RenderClear(renderer);

        int32_t windowWidth = DM->w;
        int32_t windowHeight = DM->h;
        int32_t backpackWidth = windowWidth / 2;
        int32_t backpackHeight = windowHeight - 100;
        int32_t backpackX = (windowWidth - backpackWidth) / 2;
        int32_t backpackY = (windowHeight - backpackHeight) / 2;

        SDL_Rect backpackRect = {backpackX, 20, backpackWidth, backpackHeight};

        // side
        SDL_SetRenderDrawColor(renderer, 91, 245, 173, 0xFF);
        SDL_RenderFillRect(renderer, &backpackRect);

        int32_t portraitSize = backpackWidth / 4;
        SDL_Rect portraitRect = {backpackX + backpackWidth / 20, backpackY, portraitSize, portraitSize};

        // head
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderFillRect(renderer, &portraitRect);

        // SDL_Rect personInfoRect = {backpackX + backpackWidth / 20 + portraitSize, backpackY, portraitSize, portraitSize};
        // person info
        SDL_Rect personInfoRect = {backpackX + backpackWidth / 20 + portraitSize + 50, backpackY, backpackWidth - (backpackWidth / 20 + portraitSize + 50) - 50, portraitSize + 50};
        SDL_RenderDrawRect(renderer, &personInfoRect);
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        int32_t InfoStartX = backpackX + backpackWidth / 20 + portraitSize + 50, InfoStartY = backpackY;

        char deposit_output[100];
        snprintf(deposit_output, sizeof(deposit_output), "銀子： %d 兩銀子", calPersonDeposit());
        rendertext(renderer, "font_lib/biakai.ttf", deposit_output, InfoStartX + 25, InfoStartY + 10, windowWidth, windowHeight, 24, &textColor);
        char curStatus[100];
        snprintf(curStatus, sizeof(curStatus), "位階： %s", PersonCurStatus());
        rendertext(renderer, "font_lib/biakai.ttf", curStatus, InfoStartX + 25, InfoStartY + 46, windowWidth, windowHeight, 24, &textColor);
        
        // close
        int32_t closeX = backpackX + backpackWidth - 40, closeY = backpackY - 10, closeSize = 30;
        SDL_Rect closeRect = {closeX, closeY, closeSize, closeSize};
        SDL_Surface *close = IMG_Load("img/close.png");
        if(close == NULL){
            printf("Error Read Image: %s\n", SDL_GetError());
            return 0;
        }

        SDL_Texture *close_texture = SDL_CreateTextureFromSurface(renderer, close);
        SDL_RenderCopy(renderer, close_texture, NULL, &closeRect);
        SDL_FreeSurface(close);
        SDL_DestroyTexture(close_texture);

        // name
        // set_player_name("韋小寶");
        rendertext(renderer, "font_lib/biakai.ttf", get_player_name(), backpackX + backpackWidth / 20 + portraitSize / 2 - 40, portraitRect.y + portraitRect.h + 10, windowWidth, windowHeight, 24, &textColor);

        int32_t gridCols = 5;
        int32_t gridRows = 4;
        int32_t gridCellSize = (backpackWidth - 40) / gridCols - 50; 
        int32_t gridX = backpackX + (backpackWidth - (gridCols * gridCellSize + (gridCols - 1) * 30)) / 2; // 30 代表空隙
        int32_t gridY = portraitRect.y + portraitRect.h + 10 + 50;

        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        int32_t cnt = 1;
        for(int32_t row = 0;row < gridRows;row++){
            for(int32_t col = 0;col < gridCols;col++){
                int32_t mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if(mouseX > gridX + col * (gridCellSize + 30) && mouseX < gridX + col * (gridCellSize + 30) + gridCellSize && \
                    mouseY > gridY + row * (gridCellSize + 30) && mouseY < gridY + row * (gridCellSize + 30) + gridCellSize){
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                }
                else{
                    SDL_SetRenderDrawColor(renderer, 154, 154, 154, 0xFF);
                }

                SDL_Rect cellRect = {gridX + col * (gridCellSize + 30), gridY + row * (gridCellSize + 30), gridCellSize, gridCellSize};
                SDL_RenderDrawRect(renderer, &cellRect);
                __updateBackpack(renderer, backpack, gridX + col * (gridCellSize + 30), gridY + row * (gridCellSize + 30), gridCellSize, cnt);
                cnt++;
            }
        }

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            int32_t mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(event.type == SDL_QUIT){
                quit = 1;
                // return FALSE;
                break;
            }
            else if(event.type == SDL_MOUSEBUTTONDOWN){
                if(mouseX > closeX && mouseX < closeX + closeSize && \
                    mouseY > closeY && mouseY < closeY + closeSize){
                    openBackPack = 0;
                    quit = 1;
                    // return TRUE;
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 0;
}

int32_t calPersonDeposit(){
    // pass
    return 100;
}

char* PersonCurStatus(){
    // pass
    return "可憐書生";
}

sBackPack* SetupBackpack(void){
    sBackPack *backpack = malloc(sizeof(sBackPack));
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return NULL;
    }
    backpack->pParam = malloc(sizeof(sListParam));
    backpack->pParam->size = 0;
    backpack->pParam->cmp = NULL;
    backpack->pParam->myfree = free;
    backpack->pParam->myprint = NULL;
    backpack->pHead = NULL;
    backpack->pTail = NULL;

    return backpack;
}

int8_t AddItemToBackpack(sBackPack *backpack, Item *inpData){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return FALSE;
    }
    sListNode *pNewNode = malloc(sizeof(sListNode));
    pNewNode->pData = inpData;
    pNewNode->pNext = NULL;
    if(backpack->pParam->size == 0){
        // printf("size == 0\n");
        backpack->pHead = pNewNode;
        backpack->pTail = pNewNode;
    }
    else{
        backpack->pTail->pNext = pNewNode;
        backpack->pTail = pNewNode;
    }
    backpack->pParam->size += 1;
    // if(backpack->pHead == NULL){
    //     printf("is NULL!!!!!!!!!!!!!\n");
    // }

    return TRUE;
}

int8_t RemoveItemFromBackpack(sBackPack *backpack, Item *inpData){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return FALSE;
    }
    if(backpack->pParam->cmp == NULL){
        printf( "%s(%d) %s: Not registered cmp yet!\n", __FILE__, __LINE__, __FUNCTION__ );
        return FALSE;
    }
    if(backpack->pParam->size == 0){
        return FALSE;
    }
    sListNode *pNode = backpack->pHead, *pPreNode = NULL;
    int8_t found = 0;
    while(pNode != NULL){
        if(backpack->pParam->cmp(inpData, pNode->pData) == 0){
            found = 1;
            sListNode *pTmp = pNode;
            if(pPreNode == NULL){ // head
                backpack->pHead = pNode->pNext;
                if(backpack->pHead == NULL){
                    backpack->pTail = NULL;
                }
            }
            else{
                pPreNode->pNext = pNode->pNext;
                if(backpack->pTail == pNode){
                    backpack->pTail = pPreNode;
                }
            }
            pNode = pNode->pNext;
            backpack->pParam->myfree(pTmp->pData);
            free(pTmp);
            backpack->pParam->size -= 1;
        }
        else{
            pPreNode = pNode;
            pNode = pNode->pNext;
        }
    }

    return found ? TRUE : FALSE;
}

void regCmpCallBack(sBackPack *backpack, int8_t (*cmp)(const void *, const void *)){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    backpack->pParam->cmp = cmp;
    return;
}

void regFreeCallBack(sBackPack *backpack, void (*myfree)(void *)){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    backpack->pParam->myfree = myfree;
    return;
}

void regPrintCallBack(sBackPack *backpack, void (*myprint)(const void *)){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return;
    }
    backpack->pParam->myprint = myprint;
    return;
}

static int8_t __updateBackpack(SDL_Renderer *renderer, sBackPack *backpack, int32_t x, int32_t y, int32_t CellSize, int32_t cnt){
    if(backpack == NULL){
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return FALSE;
    }
    sListNode *pNode = backpack->pHead;
    int32_t counting = 1;
    while(pNode != NULL){
        if(counting != cnt){
            pNode = pNode->pNext;
            counting++;
            continue;
        }
        char imgPath[100];
        snprintf(imgPath, sizeof(imgPath), "%s", pNode->pData->picture_file_name);
        SDL_Surface *itemImg = IMG_Load(imgPath);
        SDL_Rect img = {x, y, CellSize, CellSize};
        if(itemImg == NULL){
            printf("Error Read Image: %s\n", SDL_GetError());
            return FALSE;
        }
        SDL_Texture *itemTex = SDL_CreateTextureFromSurface(renderer, itemImg);

        SDL_RenderCopy(renderer, itemTex, NULL, &img);
        SDL_FreeSurface(itemImg);
        SDL_DestroyTexture(itemTex);

        pNode = pNode->pNext;
    }

    return TRUE;
}

int8_t printBackpackItem(sBackPack *backpack){
    if(backpack == NULL){
        printf("%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__);
        return FALSE;
    }
    if(backpack->pParam->myprint == NULL){
        printf("%s(%d) %s: Not registered myprint yet!\n", __FILE__, __LINE__, __FUNCTION__);
        return FALSE;
    }
    sListNode *pNode = backpack->pHead;
    while(pNode != NULL){
        backpack->pParam->myprint(pNode->pData);
        printf("==========\n");
        pNode = pNode->pNext;
    }
    printf("NULL\n");

    return TRUE;
}

void printBackpack(const void *ptr){
    Item *item = (Item *)ptr;
    puts("-----");
    printf("ID: %d; ", item->id);
    printf("NAME: %s; ", item->name);
    printf("Image Path: %s; ", item->picture_file_name);
    puts("\n-----");
}

int8_t cmp(const void *a, const void *b){
    Item *item1 = (Item *)a, *item2 = (Item *)b;
    return (item1->id == item2->id ? 0 : -1);
}

void myFreeFunc(void *ptr){
    Item *item = (Item *)ptr;
    if(item){
        free(item);
    }
}

int8_t cleanBackpack(sBackPack *backpack){
    if(backpack == NULL){
        printf("%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__);
        return FALSE;
    }
    sListNode *pNode = backpack->pHead;
    while(pNode != NULL){
        sListNode *pTmp = pNode;
        pNode = pNode->pNext;
        backpack->pParam->myfree(pTmp->pData);
        free(pTmp);
    }
    backpack->pHead = NULL;
    backpack->pTail = NULL;
    backpack->pParam->size = 0;

    return TRUE;
}