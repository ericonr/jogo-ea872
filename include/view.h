#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "models.h"

class View {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture, *bg,*element_texture ,*monster_texture ;
	Characters &chars;
	Scenary_element_vector &sev;
	Monster_vector &mv;

	public:
		View(Characters &chars,Scenary_element_vector &sev, Monster_vector &mv);
		~View();

		void render();
		void delay(float t);
};

struct Player {
	unsigned movement;
	unsigned long id;
	enum {keyboard, online} type;

	// keyboard
	int keys[4];
};

class Input {
	SDL_Event event;
	const Uint8 *keyboard;
	int numkeys;

	bool m_should_quit;

	public:
		std::vector<Player> player_vector;
		Input(const View &v);

		void refresh();
		bool should_quit() { return m_should_quit; }
		bool movement(int direction, unsigned n_player);
		void add_player(Player &p);
		void delete_player(int pos);
};
