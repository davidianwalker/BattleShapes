#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>

constexpr auto WIDTH = 640;
constexpr auto HEIGHT = 480;

struct Screen {
	constexpr Screen(int width, int height):
		width(width),
		height(height),
		center({ width / 2, height / 2 })
	{
	}

	const int width;
	const int height;
	const SDL_Point center;
};

constexpr const Screen gScreen{ WIDTH, HEIGHT };


#endif // SCREEN_H

