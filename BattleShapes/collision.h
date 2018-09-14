#pragma once
#include <SDL.h>
#include "player.h"
#include "attacking_shape.h"
#include "bullet.h"

/* Why collisons are not member functions of the objects.
-------------------------------------------------------------------------------
This I am less sure on. For example, if a bullet hits a shape, who's 
responsibilty is it to know what should happen? If for example you were to make
it the Bullets responsiblity, the bullet would then have to have knowledge about
all those things it could potentially collide with - and I don't think that is
right.
*/

template <typename Callable>
void check_collisions(Bullets &bullets, AttackingShapes &attacking_shapes, Callable on_bullet_hit_shape) {
	for (auto& bullet : bullets.bullets) {
		if (bullet.visible) {
			for (auto& shape : attacking_shapes.shapes) {
				if (shape.visibility) {
					if (SDL_HasIntersection(&bullet.rect, &shape.rect)) {
						shape.kill();
						bullet.kill();
						on_bullet_hit_shape();
					}
				}
			}
		}
	}
}


template <typename Callable>
void check_collisions(Player &player, AttackingShapes &attacking_shapes, Callable on_player_hit) {
	for (auto& shape : attacking_shapes.shapes) {
		if (SDL_HasIntersection(&player.rect, &shape.rect)) {
			on_player_hit();
		}
	}
}


void check_is_in_window_rect(SDL_Rect &window, AttackingShapes &attacking_shapes) {
	for (auto &shape : attacking_shapes.shapes) {
		if (shape.visibility && !SDL_HasIntersection(&shape.rect, &window)) {
			shape.visibility = false;
			printf("Killing shape. x: %f y:%f\n", shape.pos.x, shape.pos.y);
		}
	}
}


void check_is_in_window_rect(SDL_Rect &window, Bullets &bullets) {
	for (auto& bullet : bullets.bullets) {
		if (bullet.visible && !SDL_HasIntersection(&bullet.rect, &window)) {
			bullet.kill();
		}
	}
}