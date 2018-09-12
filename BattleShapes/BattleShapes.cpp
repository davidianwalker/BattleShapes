// stdlib
#include <memory>
#include <complex>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// clib
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// sdl
#include <SDL.h>
#include <SDL_stdinc.h>
#include <SDL_image.h>
#define SDL_MAIN_HANDLED 

#include "screen.h"
#include "sdl_callbacks.h"
#include "game_rect.h"
#include "attacking_shape.h"
#include "bullet.h"
#include "primitives.h"
#include "player.h"

Player player;
AttackingShapes attacking_shapes;
Bullets bullets;


void on_fire() {
	// +180 to get the bullets to fire off in the oposite direction.
	// +90 because our player image points up, but 0 degrees is to the right.
	auto angle = player.theta + 3.14 + 1.57;
	bullets.fire(angle);
}


void on_left_pressed() {
	if (!(player.rotation_direction & 0x01)) { printf("LEFT pressed\n"); }
	player.rotation_direction |= 0x01;
}


void on_left_released() {
	if (player.rotation_direction & 0x01) { printf("LEFT released\n"); }
	player.rotation_direction &= 0xFE;
}


void on_right_pressed() {
	if (!(player.rotation_direction & 0x02)) { printf("RIGHT pressed\n"); }
	player.rotation_direction |= 0x02;
}


void on_right_released() {
	if (player.rotation_direction & 0x02) { printf("RIGHT released\n"); }
	player.rotation_direction &= 0xFD;
}


bool is_collision(SDL_Rect& rect1, SDL_Rect& rect2) {
	return (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h && rect1.h + rect1.y > rect2.y);
}


int check_collisions(std::array<Bullet, 5> &bullets, std::array<int, 5> &visibility, std::array<AttackingShape, 5> &attacking_shapes) {
	int count = 0;
	for (int v = 0; v < 5; ++v) {
		if (visibility[v] == 1) {
			auto& bullet = bullets[v];

			for (auto& shape : attacking_shapes) {
				if (shape.visibility) {
					if (is_collision(bullet.rect, shape.rect)) {
						shape.visibility = false;
						visibility[v] = 0;
						++count;
					}
				}
			}
		}
	}
	return count;
}


bool check_collisions(Player &player, std::array<AttackingShape, 5> &attacking_shapes) {
	auto player_hit = false;
	for (auto& shape : attacking_shapes) {
		if (is_collision(player.rect, shape.rect)) {
			player_hit = true;
		}
	}
	return player_hit;
}

void check_is_in_window_rect(SDL_Rect &window, AttackingShapes &attacking_shapes) {
	for (auto &shape : attacking_shapes.shapes) {
		if (shape.visibility && !is_collision(shape.rect, window)) {
			shape.visibility = false;
			printf("Killing shape. x: %f y:%f\n", shape.pos.x, shape.pos.y);
		}
	}
}

void check_is_in_window_rect(SDL_Rect &window, Bullets &bullets) {
	for (int i = 0; i < bullets.visibility.size(); ++i) {
		auto &visibilty = bullets.visibility[i];
		if (visibilty == 1 && !is_collision(bullets.bullets[i].rect, window)) {
			visibilty = 0;
			printf("Killing bullet.\n");
		}
	}
}


int main() {
	srand(time(nullptr));
	sdl_init();
	int total_score = 0;

	// LESSION: Ownership transfer.
	Screen screen(WIDTH, HEIGHT);
	SDL_Window_Uptr window{ make_window(screen) };
	SDL_Renderer_Uptr renderer{ make_renderer(window.get()) };
	SDL_Texture_Uptr player_texture{ make_texture(renderer.get(), "resources/playermclaren.png") };
	
	std::string font_name = "resources/OpenSans-Regular.ttf";
	auto font = load_font(font_name);
	const SDL_Color black = { 0, 0, 0 };

	// Init game objects
	// --------------------------------------------------------------------------
	auto background_rect = SDL_Rect{ 0, 0, screen.width, screen.height };
	attacking_shapes.init();
	bullets.init();
	player.init(screen.center.x, screen.center.y);

	// Run the game loop.
	// ------------------------------------------------------------------------
	for (int i = 0; i < 500; i++) {
		fflush(stdout);
		// LESSION: Callbacks should be lambdas to pass through data by capture.
		sdl_handle_input(on_fire, on_left_pressed, on_right_pressed, on_left_released, on_right_released);

		// Update each of the game objects.
		player.tick();
		attacking_shapes.tick();
		bullets.tick();

		total_score += check_collisions(bullets.bullets, bullets.visibility, attacking_shapes.shapes);
		if (check_collisions(player, attacking_shapes.shapes)) {
			total_score = 0;
		}

		check_is_in_window_rect(background_rect, attacking_shapes);
		check_is_in_window_rect(background_rect, bullets);

		// Render the game objects
		// --------------------------------------------------------------------------

		// Clear the screen
		SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer.get(), &background_rect);

		// Render the player.
		SDL_RenderCopyEx(renderer.get(), player_texture.get(), NULL, &player.rect, player.theta * 180 / 3.14, nullptr, SDL_FLIP_NONE);

		// Render the attacking shapes.
		for (auto& shape : attacking_shapes.shapes) {
			if (shape.visibility) {
				SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(renderer.get(), &shape.rect);
			}
		}

		// Render the bullets.
		for (int v = 0; v < 5; ++v) {
			if (bullets.visibility[v] == 1) {
				auto& bullet = bullets.bullets [v];
				SDL_SetRenderDrawColor(renderer.get(), 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderFillRect(renderer.get(), &bullet.rect);
			}
		}

		//Render the score.
		auto font_surface = font_create_surface(font.get(), std::to_string(total_score), black);
		auto font_texture = font_create_texture(font_surface.get(), renderer.get());

		SDL_Rect dst{ 0, 0, font_surface->w, font_surface->h };
		SDL_RenderCopy(renderer.get(), font_texture.get(), nullptr, &dst);

		// Update the screen with rendering actions
		SDL_RenderPresent(renderer.get());

		SDL_Delay(10);
	}

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}
