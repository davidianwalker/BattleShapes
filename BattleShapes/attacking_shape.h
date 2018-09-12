#ifndef ATTACKING_SHAPE_H
#define ATTACKING_SHAPE_H

#include <array>
#include <SDL.h>
#include "primitives.h"

struct AttackingShape {
    Pos pos = {0, 0};
    float theta = 0;
	bool visibility = false;
    SDL_Rect rect = {0, 0, 32, 32}; // x, y, w h

	void init();
	void tick();
};

struct AttackingShapes {
	std::array<AttackingShape, 5> shapes;
	int count_down;
	void tick();
	void init();
};



#endif // ATTACKING_SHAPE_H
