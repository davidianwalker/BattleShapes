#include "attacking_shape.h"
#include <cstdlib>
#include <complex>
#include <tuple>
#include "screen.h"


std::tuple<float, float, float> calculate_starting_pos() {
	auto angle = (rand() % 10) *
		36.0f;  // 10 starting points about the circle seems enough.
	auto theta = angle * RADIANS;

	auto r = gScreen.height / 2.0f;
	auto cart = std::polar<float>(r, theta);

	auto x = gScreen.center.x + cart.real() - 16.0f;
	auto y = gScreen.center.y + cart.imag() - 16.0f;

	auto itheta = atan2(gScreen.center.y - 16 - y, gScreen.center.x - 16 - x);
	if (itheta < 0.0) {
		itheta += (2 * pi);
	}

	return std::make_tuple(x, y, itheta);
}


StartingPos AttackingShapes::get_starting_pos() {
	auto pos = static_cast<int>(rand() % 10);
	return this->table.values[pos];
}



void AttackingShape::init(StartingPos const& pos) {
	float x, y, itheta;
	std::tie(x, y, itheta) = pos;
	this->pos.x = x;
	this->pos.y = y;
	this->theta = itheta;
	this->rect.x = static_cast<int>(x + 0.5f);
	this->rect.y = static_cast<int>(y + 0.5f);
	this->visibility = true;
}


void AttackingShape::tick() {
    auto dx = 1.0f * cos(this->theta);
    auto dy = 1.0f * sin(this->theta);
	this->pos.x += dx;
	this->pos.y += dy;
	this->rect.x = static_cast<int>(this->pos.x + 0.5f );
	this->rect.y = static_cast<int>(this->pos.y + 0.5f);
}


void AttackingShape::kill() {
	this->visibility = false;
}

// ----------------------------------------------------------------------------

void AttackingShapes::init() {
	count_down = 20;
}


void AttackingShapes::tick() {
	if (--count_down <= 0) {
		// PRACTICAL 2 - Using std::algorithm to replace a for-loop.
		for (auto& shape : this->shapes) {
			if (shape.visibility == false) {
				// Generate the staring positions at run time.
				shape.init(calculate_starting_pos());

				// PRACTICAL 6 - using constexpr to calculate positions at compile time.
				// Generate the starting positions at compile time - this doesn't work yet!
				// shape.init(this->get_starting_pos());
				break;
			}
		}

		count_down = 100;
	}

	for (auto& shape : this->shapes) {
		if (shape.visibility) {
			shape.tick();
		}
	}
}
