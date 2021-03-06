#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "sdl_types.h"
#include "primitives.h"

struct Player {
    Pos pos = {0, 0};
    float theta = 0;
    SDL_Rect rect = {0, 0, 32, 32}; // x, y, w h
    uint8_t rotation_direction;
	SDL_Texture* texture{ nullptr };

	void init(SDL_Texture* texture, SDL_Point const& center);
	void tick();
};



#endif // PLAYER_H
