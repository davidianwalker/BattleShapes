#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "primitives.h"

struct Player {
    Pos pos = {0, 0};
    float theta = 0;
    SDL_Rect rect = {0, 0, 32, 32}; // x, y, w h
    uint8_t rotation_direction;

	void init(int origin_x, int origin_y);
	void tick();
};



#endif // PLAYER_H
