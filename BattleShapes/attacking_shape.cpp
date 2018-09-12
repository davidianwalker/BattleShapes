#include "attacking_shape.h"
#include <cstdlib>
#include <complex>
#include "screen.h"

constexpr const auto pi = 3.141592f;
constexpr const auto RADIANS = pi / 180.0f;

void AttackingShape::init() {
  auto angle = (rand() % 10) *
               36.0f;  // 10 starting points about the circle seems enough.
  auto theta = angle * RADIANS;

  auto r = gScreen.height / 2.0f;
  auto cart = std::polar<float>(r, theta);
  // printf("theta %f  ", theta);

  auto x = gScreen.center.x + cart.real() - 16.0f;
  auto y = gScreen.center.y + cart.imag() - 16.0f;
  // printf("x %f  ", x);
  // printf("y %f\n", y);

  auto itheta = atan2(gScreen.center.y - 16 - y, gScreen.center.x - 16 - x);
  if (itheta < 0.0) {
    itheta += (2 * pi);
  }

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

// ----------------------------------------------------------------------------

void AttackingShapes::init() {
	count_down = 20;
}


void AttackingShapes::tick() {
	if (--count_down <= 0) {
		// Make shape alive.
		auto it = std::find_if(shapes.begin(), shapes.end(), [](const AttackingShape& shape) {
			return !shape.visibility;
		});

		if (it != shapes.end()) {
			it->init();
		}

		count_down = 100;
	}

	for (auto& shape : this->shapes) {
		if (shape.visibility) {
			shape.tick();
		}
	}
}
