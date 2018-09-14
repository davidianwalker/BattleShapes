#include "bullet.h"
#include "screen.h"

void Bullet::init(SDL_Point const&center, float theta) {
	this->visible = true;
	this->theta = theta;

	int w = this->rect.w;
	int h = this->rect.h;
	// We need pos because SDL_Rect coordinates are ints. 
	// The change in position per update is < 1 therefore the truncation that 
	// would occur casting to int would mean the bullets wouldn't go anywhere!
	this->pos.x = center.x - w / 2.0f;
	this->pos.y = center.y - h / 2.0f;
	this->rect.x = center.x - w / 2;
	this->rect.y = center.y - h / 2;
}

void Bullet::tick() {
	// We need pos because SDL_Rect coordinates are ints. 
	// The change in position per update is < 1 therefore the truncation that 
	// would occur casting to int would mean the bullets wouldn't go anywhere!
	float dx = static_cast<float>(1.0 * cos(this->theta));
	float dy = static_cast<float>(1.0 * sin(this->theta));
	this->pos.x += dx*1.5;
	this->pos.y += dy*1.5;
	this->rect.x = static_cast<int>(this->pos.x);
	this->rect.y = static_cast<int>(this->pos.y);
}

void Bullet::kill() {
	this->visible = false;
}

void Bullets::init() { }


void Bullets::tick() {
	for (auto it = this->first; it != this->bullets.end(); ++it) {
		it->tick();
	}
}


void Bullets::fire(float theta) {
	if (count < 5) {
		count++;
		// Remember bullets fill up from the back.
		--(this->first);

		first->init(gScreen.center, theta);
	}

	//for (auto i = 1; i < 5; ++i) {
	//	if (this->bullets[i].visible == false) {
	//		this->bullets[i].init(gScreen.center, theta);
	//		break;
	//	}
	//}
}

void Bullets::kill(decltype(bullets.end()) it) {
	// Remember bullets fill up from the back.
	std::swap(*this->first, *it);
	this->first = it + 1;
	--count;
}