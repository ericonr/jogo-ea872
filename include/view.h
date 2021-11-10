#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "json.hpp"

#include "models.h"

class View
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture, *bg, *element_texture, *monster_texture, *banana_texture;
	Characters &chars;
	Scenery_element_vector &sev;
	Monster_vector &mv;
	Projectile_vector &pv;

	public:
	View(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv);
	~View();

	void render();
	void delay(float t);
};

class Input
{
	SDL_Event event;
	const Uint8 *keyboard;
	int numkeys;

	bool m_should_quit;
	unsigned m_movement;

	public:
	Input(const View &v);

	void refresh();
	bool should_quit()
	{
		return m_should_quit;
	}
	void to_json(nlohmann::json &j);
};
