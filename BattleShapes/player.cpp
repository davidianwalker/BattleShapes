#include "player.h"
#include "stdio.h"

void Player::init(SDL_Texture_Uptr texture, SDL_Point const& center) {
	this->texture = std::move(texture);

	auto x = center.x;
	auto y = center.y;
    auto w = this->rect.w / 2.0f;
    auto h = this->rect.h / 2.0f;
	this->pos.x = x - w;
	this->pos.y = y - h;

	// +0.5f because casting to int always rounds down.
	this->rect.x = static_cast<int>((x - w) + 0.5f);
	this->rect.y = static_cast<int>((y - h) + 0.5f);
}

void Player::tick() {
    int direction = 0;
    if (this->rotation_direction & 0x01) { direction -= 1; }
    if (this->rotation_direction & 0x02) { direction += 1; }
    if (direction != 0) {
		this->theta += (direction * 0.1f); 
    }
}
