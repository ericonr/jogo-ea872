#include <stdexcept>

#include "view.h"

const static int SCREEN_WIDTH = 640;
const static int SCREEN_HEIGHT = 480;

// 1m = 10px
const static float px_per_m = 10.;

static int adjust_coord(float pos, int object_size, int max_size)
{
	return (int)(pos * px_per_m) + max_size / 2 - object_size / 2;
}

static int adjust_x(float pos, int object_size)
{
	return adjust_coord(pos, object_size, SCREEN_WIDTH);
}

static int adjust_y(float pos, int object_size)
{
	return adjust_coord(-pos, object_size, SCREEN_HEIGHT);
}

View::View(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv)
	: window(nullptr), renderer(nullptr), texture(nullptr), bg(nullptr), element_texture(nullptr), chars(chars),
	  sev(sev), mv(mv), pv(pv)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(SDL_GetError());
	}
	window = SDL_CreateWindow("Massa mola", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
							  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		SDL_Quit();
		throw std::runtime_error(SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		throw std::runtime_error(SDL_GetError());
	}

	texture = IMG_LoadTexture(renderer, "resources/img/capi.png");
	bg = IMG_LoadTexture(renderer, "resources/img/bg.png");
	element_texture = IMG_LoadTexture(renderer, "resources/img/rock.png");
	monster_texture = IMG_LoadTexture(renderer, "resources/img/gorilla.png");
	banana_texture = IMG_LoadTexture(renderer, "resources/img/banana.png");
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
	SDL_RenderCopy(renderer, bg, nullptr, nullptr);

	for (auto character : chars.Character_vector) {
		target.w = target.h = character.size;
		target.x = adjust_x(character.x, target.w);
		target.y = adjust_y(character.y, target.h);

		SDL_RenderCopy(renderer, texture, nullptr, &target);
	}

	for (auto element : sev.element_vector) {
		target.w = target.h = element.size;
		target.x = adjust_x(element.x, target.w);
		target.y = adjust_y(element.y, target.h);

		SDL_RenderCopy(renderer, element_texture, nullptr, &target);
	}

	for (auto monster : mv.enemy_vector) {
		target.w = target.h = monster.size;
		target.x = adjust_x(monster.x, target.w);
		target.y = adjust_y(monster.y, target.h);

		SDL_RenderCopy(renderer, monster_texture, nullptr, &target);
	}

	for (auto p : pv.all_projectile_vector) {
		target.w = target.h = 20;
		target.x = adjust_x(p.x, target.w);
		target.y = adjust_y(p.y, target.h);
		SDL_RenderCopy(renderer, banana_texture, nullptr, &target);
	}

	SDL_RenderPresent(renderer);
}

void View::delay(float t)
{
	SDL_Delay(t * 1000);
}
