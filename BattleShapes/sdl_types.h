#pragma once
#include <memory>
#include <SDL_image.h>
#include <SDL_ttf.h>
using SDL_Window_Uptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using SDL_Renderer_Uptr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
using SDL_Texture_Uptr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
using TTF_Font_Uptr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;
using SDL_Surface_Uptr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;