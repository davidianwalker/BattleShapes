#ifndef BULLET_H
#define BULLET_H

#include <array>
#include <SDL.h>
#include "primitives.h"

struct Bullet {
    Pos pos = {0, 0};
    float theta = 0;
    SDL_Rect rect = {0, 0, 16, 16}; // x, y, w h
	bool visible = false;

	void init(SDL_Point const&center, float theta);
	void tick();
	void kill();
};


struct Bullets {
	std::array<Bullet, 5> bullets;
	decltype(bullets.end()) first = bullets.end();
	int count = 0;

	void init();
	void tick();
	void fire(float theta);
	void kill(decltype(bullets.end()));
};

#endif // BULLET_H
