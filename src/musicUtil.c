#include "musicUtil.h"

// 給像是背景音樂這種比較長的音樂
int8_t PlayMusic(const char *musicPath, Mix_Music *music, int32_t volume){
    music = Mix_LoadMUS(musicPath);
    Mix_VolumeMusic(volume); // 0~128
    if(music == NULL){
        printf("Mixer Error: %s\n", Mix_GetError());
        return FALSE;
    }
    if(Mix_PlayMusic(music, -1) == -1){ // infinity: -1
        printf("Mixer Error: %s\n", Mix_GetError());
        return FALSE;
    }

    return TRUE;
}

// 短暫的音效
int8_t PlayChunk(const char *musicPath, Mix_Chunk *sound, int32_t channel, int32_t volume, int32_t repeat){
    sound = Mix_LoadWAV(musicPath);
    Mix_Volume(channel, volume);
    if(sound == NULL){
        printf("Mixer Error: %s\n", Mix_GetError());
        return FALSE;
    }
    if(Mix_PlayChannel(channel, sound, repeat) == -1){ // infinity: -1
        printf("Mixer Error: %s\n", Mix_GetError());
        return FALSE;
    }
    return TRUE;
}