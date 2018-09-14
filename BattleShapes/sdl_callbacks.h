#ifndef SDL_CALLBACKS_H
#define SDL_CALLBACKS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#undef main
#include <string>

#include "screen.h"
#include "sdl_types.h"

void sdl_init();

void sdl_handle_input(void (*on_fire)(),
                      void (*on_left)(),
                      void (*on_right)(),
                      void (*on_left_released)(),
                      void (*on_right_released)());


SDL_Window_Uptr make_window(Screen &screen);

SDL_Renderer_Uptr make_renderer(SDL_Window* window);

SDL_Texture* sdl_load_texture(const std::string& path, SDL_Renderer *renderer);

TTF_Font_Uptr load_font(std::string const& font);

SDL_Texture_Uptr font_create_texture(SDL_Surface* surface, SDL_Renderer *renderer);
SDL_Surface_Uptr font_create_surface(TTF_Font* font, std::string const& text, SDL_Color const& color);

#endif // SDL_CALLBACKS_H
