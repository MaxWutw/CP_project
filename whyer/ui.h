#ifndef UI_H
#define UI_H

void renderText(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h);
void renderChoices(SDL_Renderer* renderer);
void renderLuckBar(SDL_Renderer* renderer, int luckValue);

#endif
