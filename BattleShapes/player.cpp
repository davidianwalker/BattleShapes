#include "player.h"
#include "stdio.h"

void Player::init(SDL_Texture_Uptr texture, int origin_x, int origin_y) {
	this->texture = std::move(texture);

    int w = this->rect.w;
    int h = this->rect.h;
	this->pos.x = origin_x - w / 2.0f;
	this->pos.y = origin_y - h / 2.0f;
	this->rect.x = origin_x - w / 2;
	this->rect.y = origin_y - h / 2;
}

void Player::tick() {
    int direction = 0;
    if (this->rotation_direction & 0x01) { direction -= 1; }
    if (this->rotation_direction & 0x02) { direction += 1; }
    if (direction != 0) {
		this->theta += (direction * 0.1f);
        printf("theta: %f\n", this->theta);
    }
}
