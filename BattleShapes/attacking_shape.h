#ifndef ATTACKING_SHAPE_H
#define ATTACKING_SHAPE_H

#include <array>
#include <SDL.h>
#include "primitives.h"

constexpr const auto pi = 3.141592f;
constexpr const auto RADIANS = pi / 180.0f;

using StartingPos = std::tuple<float, float, float>;

constexpr const auto NUM_POS = 10;
constexpr const auto ANGLE_PER_POS = 360.0f / NUM_POS;


template<int N>
struct Table
{
	constexpr Table() : values() {
		auto angle = 0.0f;

		for (auto &value : values) {
			// TODO: This is incomplete - look at calculate_starting_pos for hints.

			value = std::make_tuple(0, 0, 0);
			angle += ANGLE_PER_POS;
		}
	}

	std::array<StartingPos, NUM_POS> values;
};


struct AttackingShape {
    Pos pos = {0, 0};
    float theta = 0;
	bool visibility = false;
    SDL_Rect rect = {0, 0, 32, 32};

	void init(StartingPos const& pos);
	void tick();
	void kill();
};

struct AttackingShapes {
	Table<NUM_POS> table;
	std::array<AttackingShape, 5> shapes;
	int count_down;
	void tick();
	void init();
	StartingPos get_starting_pos();
};



#endif // ATTACKING_SHAPE_H
