#include "game.h"

void handleChoice(GameState* state, int choice) {
    switch (*state) {
        case STATE_BIRTH:
            if (choice == 1) {
                *state = STATE_CHILDHOOD;
            } else if (choice == 2) {
                *state = STATE_ADULTHOOD;
            } else {
                *state = STATE_OLDAGE;
            }
            break;
        case STATE_CHILDHOOD:
            if (choice == 1) {
                *state = STATE_ADULTHOOD;
            } else if (choice == 2) {
                *state = STATE_OLDAGE;
            } else {
                *state = STATE_END;
            }
            break;
        case STATE_ADULTHOOD:
            if (choice == 1) {
                *state = STATE_OLDAGE;
            } else if (choice == 2) {
                *state = STATE_END;
            } else {
                *state = STATE_END;
            }
            break;
        case STATE_OLDAGE:
            *state = STATE_END;
            break;
        case STATE_END:
            break;
    }
}

const char* getDialogText(GameState state) {
    switch (state) {
        case STATE_BIRTH: return "Please select birth family ~";
        case STATE_CHILDHOOD: return "childhood ~";
        case STATE_ADULTHOOD: return "adulthood ~";
        case STATE_OLDAGE: return "oldage ~";
        case STATE_END: return "end ~";
        default: return "";
    }
}

int getLuckValue(GameState state) {
    switch (state) {
        case STATE_BIRTH: return 70;
        case STATE_CHILDHOOD: return 50;
        case STATE_ADULTHOOD: return 30;
        case STATE_OLDAGE: return 10;
        case STATE_END: return 0;
        default: return 0;
    }
}