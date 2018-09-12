#pragma once

#include <SDL.h>
#include "bullet.h"
#include "attacking_shape.h"

/* Why render is not a member function of the objects.
  ----------------------------------------------------
  Rendering is a very application specific thing, for example consider what would happen if we stoped using SDL.
  If render was a member function, if we wanted to reuse any of the components, then we'd always drag in SDL even
  if we didn't want to use it.
*/


inline void render(SDL_Renderer* renderer, Bullets const& bullets) {
	for (int v = 0; v < 5; ++v) {
		if (bullets.visibility[v] == 1) {
			auto& bullet = bullets.bullets[v];
			SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &bullet.rect);
		}
	}
}

inline void render(SDL_Renderer* renderer, AttackingShapes const& attacking_shapes) {
	for (auto& shape : attacking_shapes.shapes) {
		if (shape.visibility) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &shape.rect);
		}
	}
}


inline void render(SDL_Renderer* renderer, Player const& player) {
	SDL_RenderCopyEx(renderer, 
		player.texture.get(), 
		NULL, 
		&player.rect,
		player.theta * 180 / 3.14, 
		nullptr, 
		SDL_FLIP_NONE);
}


const SDL_Color black = { 0, 0, 0 };

inline void render_score(SDL_Renderer* renderer, TTF_Font *font, int total_score) {
	auto font_surface = font_create_surface(font, std::to_string(total_score), black);
	auto font_texture = font_create_texture(font_surface.get(), renderer);

	SDL_Rect dst{ 0, 0, font_surface->w, font_surface->h };
	SDL_RenderCopy(renderer, font_texture.get(), nullptr, &dst);
}