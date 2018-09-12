 #include "bullet.h"
#include "screen.h"

void bullet_init(Bullet& bullet, SDL_Point const&center) {
    int w = bullet.rect.w;
    int h = bullet.rect.h;
    bullet.pos.x = center.x - w / 2.0f;
    bullet.pos.y = center.y - h / 2.0f;
    bullet.rect.x = center.x - w / 2;
    bullet.rect.y = center.y - h / 2;
}

void bullet_tick(Bullet &bullet) {
    float dx = static_cast<float>(1.0 * cos(bullet.theta));
    float dy = static_cast<float>(1.0 * sin(bullet.theta));
    bullet.pos.x += dx*1.5;
    bullet.pos.y += dy*1.5;
    bullet.rect.x = static_cast<int>(bullet.pos.x);
    bullet.rect.y = static_cast<int>(bullet.pos.y);
}

void Bullets::init() {
	for (auto& v : this->visibility) {
		v = 0;
	}
}


void Bullets::tick() {
	for (int v = 0; v < 5; ++v) {
		if (this->visibility[v] == 1) {
			auto& bullet = this->bullets[v];
			bullet_tick(bullet);
		}
	}
}


void Bullets::fire(float theta) {
	for (int i = 0; i < this->visibility.size(); ++i) {
		if (this->visibility[i] == 0) {
			this->visibility[i] = 1;
			bullet_init(this->bullets[i], gScreen.center);
			this->bullets[i].theta = theta;
			break;
		}
	}
}