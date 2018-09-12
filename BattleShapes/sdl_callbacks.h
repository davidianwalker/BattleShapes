#ifndef SDL_CALLBACKS_H
#define SDL_CALLBACKS_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#undef main
#include <string>
#include <memory>

#include "screen.h"

void sdl_init();

void sdl_handle_input(void (*on_fire)(),
                      void (*on_left)(),
                      void (*on_right)(),
                      void (*on_left_released)(),
                      void (*on_right_released)());

using SDL_Window_Uptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
SDL_Window_Uptr make_window(Screen &screen);

using SDL_Renderer_Uptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
SDL_Renderer_Uptr make_renderer(SDL_Window* window);

using SDL_Texture_Uptr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
SDL_Texture_Uptr sdl_load_texture(const std::string& path, SDL_Renderer *renderer);
SDL_Texture_Uptr make_texture(SDL_Renderer *renderer, std::string const& filename);

using TTF_Font_Uptr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
TTF_Font_Uptr load_font(std::string const& font);

using SDL_Surface_Uptr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

SDL_Texture_Uptr font_create_texture(SDL_Surface* surface, SDL_Renderer *renderer);
SDL_Surface_Uptr font_create_surface(TTF_Font* font, std::string const& text, SDL_Color const& color);

#endif // SDL_CALLBACKS_H
