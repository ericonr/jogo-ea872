#include <stdexcept>

#include "view.h"

const static int SCREEN_WIDTH = 640;
const static int SCREEN_HEIGHT = 480;

// 1m = 10px
const static float px_per_m = 10.;

static int adjust_coord(float pos, int object_size, int max_size)
{
	return (int)(pos * px_per_m) + max_size/2 - object_size/2;
}

static int adjust_x(float pos, int object_size)
{
	return adjust_coord(pos, object_size, SCREEN_WIDTH);
}

static int adjust_y(float pos, int object_size)
{
	return adjust_coord(-pos, object_size, SCREEN_HEIGHT);
}

View::View(Characters &chars):
	window(nullptr), renderer(nullptr),
	texture(nullptr), bg(nullptr), chars(chars)
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
	SDL_Rect target;

	SDL_RenderClear(renderer);

	


	for(unsigned int n_player = 0;n_player < chars.Character_vector.size();n_player++){

	target.w = target.h = chars.Character_vector[n_player].size;
	target.x = adjust_x(chars.Character_vector[n_player].x, target.w);
	target.y = adjust_y(chars.Character_vector[n_player].y, target.h);

	std::cout <<"posição em x do player "<< n_player << "\r\n" << target.x<< "\r\n" ;
	std::cout <<"posição em y do player "<< n_player << "\r\n" << target.y<< "\r\n" ;


	SDL_RenderCopy(renderer, bg, nullptr, nullptr);
	SDL_RenderCopy(renderer, texture, nullptr, &target);
	SDL_RenderPresent(renderer);
	}
		
}

void View::delay(float t)
{
	SDL_Delay(t * 1000);
}
