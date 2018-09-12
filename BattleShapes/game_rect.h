#ifndef GAME_RECT_H
#define GAME_RECT_H

#include <SDL.h>

struct GameRect
{
    float x = 0;
    float y = 0;
    float theta = 0;
    SDL_Rect rect;
};

#endif // GAME_RECT_H
