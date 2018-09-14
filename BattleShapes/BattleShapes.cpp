// stdlib
#include <memory>
#include <complex>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

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
#include "render.h"
#include "collision.h"


// Bullets and Player need to be global because I am lazy and don't want to
// refactor how the player input works.
Player player;
Bullets bullets;
AttackingShapes attacking_shapes;


void on_fire() {
	// +180 to get the bullets to fire off in the oposite direction.
	// +90 because our player image points up, but 0 degrees is to the right.
	constexpr auto bullet_angle_offset = 3.14f + 1.57f;
	auto angle = player.theta + bullet_angle_offset;
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


int main() {
	srand(time(nullptr));
	sdl_init();
	auto total_score = 0;

	// LESSION: Ownership transfer.
	Screen screen(WIDTH, HEIGHT);
	SDL_Window_Uptr window{ make_window(screen) };
	SDL_Renderer_Uptr renderer{ make_renderer(window.get()) };
	// PRACTICAL 3: Using std::unique_ptr.
	SDL_Texture* player_texture{ sdl_load_texture("resources/playermclaren.png", renderer.get()) };
	
	std::string font_name = "resources/OpenSans-Regular.ttf";
	auto font = load_font(font_name);

	// Init game objects
	// --------------------------------------------------------------------------
	auto background_rect = SDL_Rect{ 0, 0, screen.width, screen.height };
	attacking_shapes.init();
	bullets.init();
	player.init(player_texture, screen.center);

	// Run the game loop.
	// ------------------------------------------------------------------------
	for (int i = 0; i < 500; i++) {
		fflush(stdout);
		// Handle player input.
		// --------------------------------------------------------------------
		sdl_handle_input(on_fire, on_left_pressed, on_right_pressed, on_left_released, on_right_released);

		// Update game objects.
		// --------------------------------------------------------------------
		player.tick();
		attacking_shapes.tick();
		bullets.tick();

		// Check collisions
		// See collision.h for explanation for why these aren't member 
		// functions.
		// Note, lambda functions are used for customisation points.
		// --------------------------------------------------------------------
		check_collisions(bullets, attacking_shapes, [&total_score]() {
			total_score += 1;
		});
		check_collisions(player, attacking_shapes, [&total_score]() {
			total_score = 0;
		});

		check_is_in_window_rect(background_rect, attacking_shapes);
		check_is_in_window_rect(background_rect, bullets);

 		// Render the game objects
		// --------------------------------------------------------------------
		// Clear the screen
		SDL_SetRenderDrawColor(renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderFillRect(renderer.get(), &background_rect);

		// Render the objects.
		// See render.h for explanation to why render is not a member function of the objects.
		render(renderer.get(), player);
		render(renderer.get(), attacking_shapes);
		render(renderer.get(), bullets);
		render_score(renderer.get(), font.get(), total_score);

		// Update the screen with rendering actions
		SDL_RenderPresent(renderer.get());

		SDL_Delay(10);
	}

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}
