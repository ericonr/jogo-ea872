#include <stdexcept>

#include "view.h"

const static int SCREEN_WIDTH = 640;
const static int SCREEN_HEIGHT = 480;

static int ajustar_coord(float pos, int dimensao_objeto, int dimensao_max)
{
	// 1m = 100px
	return (int)(pos * 100.) + dimensao_max/2 - dimensao_objeto/2;
}

View::View(Character &c):
	window(nullptr), renderer(nullptr),
	texture(nullptr), bg(nullptr), c(c)
{
	if (SDL_Init (SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	window = SDL_CreateWindow("Massa mola",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Quit();
		throw std::runtime_error(SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw std::runtime_error(SDL_GetError());
	}

	texture = IMG_LoadTexture(renderer, "resources/img/capi.png");
	bg = IMG_LoadTexture(renderer, "resources/img/park.jpeg");
	SDL_QueryTexture(texture, nullptr, nullptr, &target.w, &target.h);
}

View::~View()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(bg);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void View::render()
{
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, bg, nullptr, nullptr);
	target.x = ajustar_coord(c.x, target.w, SCREEN_WIDTH);
	target.y = ajustar_coord(c.y, target.h, SCREEN_HEIGHT);
	SDL_RenderCopy(renderer, texture, nullptr, &target);

	SDL_RenderPresent(renderer);
}

void View::delay(float t)
{
	SDL_Delay(t * 1000);
}
