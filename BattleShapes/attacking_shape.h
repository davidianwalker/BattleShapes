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
			auto theta = angle * RADIANS;

			auto r = gScreen.height / 2.0f;
			auto cart = std::polar<float>(r, theta);

			auto x = gScreen.center.x + cart.real() - 16.0f;
			auto y = gScreen.center.y + cart.imag() - 16.0f;

			auto itheta = atan2(gScreen.center.y - 16 - y, gScreen.center.x - 16 - x);
			if (itheta < 0.0) {
				itheta += (2 * pi);
			}

			value = std::make_tuple(x, y, itheta);
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
