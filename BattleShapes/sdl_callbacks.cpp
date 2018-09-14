#include <stdio.h>
#include "sdl_callbacks.h"
#include "screen.h"


void sdl_print_error(const char*msg) {
    printf("%s\nSDL Error: %s\n", msg, SDL_GetError());
}


void sdl_print_image_error(const char* msg) {
    printf("%s\nSDL Image Error: %s\n", msg, IMG_GetError());
}


void sdl_print_ttf_error(const char* msg) {
	printf("%s\nTTF Error: %s\n", msg, TTF_GetError());
}


void sdl_init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		sdl_print_error("SDL_INIT_VIDEO failed.");
		exit(-1);
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		sdl_print_image_error("IMG_INIT_PNG failed.");
		exit(-2);
	}

	if (TTF_Init() == -1) {
		sdl_print_ttf_error("TTF_Init failed.");
		exit(-5);
	}
}


SDL_Renderer_Uptr make_renderer(SDL_Window* window)
{
	auto* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		sdl_print_error("SDL_CreateRenderer Failed. Got nullptr.");
	}

	return { renderer, &SDL_DestroyRenderer };
}


SDL_Window_Uptr make_window(Screen &screen)
{
	auto* window = SDL_CreateWindow("Battle Shapes",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screen.width,
		screen.height,
		SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		sdl_print_error("SDL_CreateWindow Failed. Got nullptr.");
	}

	return { window, SDL_DestroyWindow };
}


SDL_Texture* sdl_load_texture(const std::string& path, SDL_Renderer *renderer) {
    SDL_Texture* new_texture = nullptr;

    // Load image at specified path
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());

    if (loaded_surface) {
        //Create texture from surface pixels
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

        if (new_texture == nullptr) {
            auto msg = std::string("Unable to create texture from: ") + path;
            sdl_print_error(msg.c_str());
			exit(-4);
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loaded_surface);
	}
	else {
		auto msg = std::string("Unable to load image: ") + path;
		sdl_print_image_error(msg.c_str());
	}

	return new_texture;
}


TTF_Font_Uptr load_font(std::string const& font_name) {

	//Open the font 
	auto* font = TTF_OpenFont(font_name.c_str(), 28);
	if (font == nullptr) {
		printf("Failed to %s. SDL_ttf Error: %s\n", font_name.c_str(), TTF_GetError());
		exit(-6);
	}

	return { font, TTF_CloseFont };
}


SDL_Surface_Uptr font_create_surface(TTF_Font* font, std::string const& text, SDL_Color const& color)
{
	auto* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (textSurface == nullptr) {
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		exit(-7);
	}

	return { textSurface, SDL_FreeSurface };
}


SDL_Texture_Uptr font_create_texture(SDL_Surface* surface, SDL_Renderer *renderer)
{
	// Create texture from surface pixels
	auto* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == nullptr) {
		printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		exit(-8);
	}

	return { texture, SDL_DestroyTexture };
}


void sdl_handle_input(void(*on_fire)(),
	void(*on_left)(),
	void(*on_right)(),
	void(*on_left_released)(),
	void(*on_right_released)()) {
	SDL_Event event;
	const Uint8* key_states = SDL_GetKeyboardState(nullptr);


	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_KEYDOWN: {
		if (event.key.keysym.sym == SDLK_SPACE) {
			on_fire();
		}
	}
	}

	if (key_states[SDL_SCANCODE_LEFT]) {
		on_left();
	}
	else {
		on_left_released();
	}


	if (key_states[SDL_SCANCODE_RIGHT]) {
		on_right();
	}
	else {
		on_right_released();
	}
}