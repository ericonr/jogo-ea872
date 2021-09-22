#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "models.h"

class View {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture, *bg;
	Characters &chars;

	public:
		View(Characters &chars);
		~View();

		void render();
		void delay(float t);
};

namespace direction {
	const int up = 0, down = 1, left = 2, right = 3;
	const int max = 4;
}

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
