#ifndef BULLET_H
#define BULLET_H

#include <array>
#include <SDL.h>
#include "primitives.h"

struct Bullet {
    Pos pos = {0, 0};
    float theta = 0;
    SDL_Rect rect = {0, 0, 16, 16}; // x, y, w h
};

void bullet_init(Bullet& rect, SDL_Point const&center);

void bullet_tick(Bullet& bullet);

struct Bullets {
	std::array<Bullet, 5> bullets;
	std::array<int, 5> visibility;

	void init();
	void tick();

	void fire(float theta);
};

#endif // BULLET_H
