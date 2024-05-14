#ifndef GAME_H
#define GAME_H

typedef enum {
    STATE_BIRTH,
    STATE_CHILDHOOD,
    STATE_ADULTHOOD,
    STATE_OLDAGE,
    STATE_END
} GameState;

void handleChoice(GameState* state, int choice);
const char* getDialogText(GameState state);
int getLuckValue(GameState state);

#endif
