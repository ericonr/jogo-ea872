#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "models.h"

class View {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture, *bg;
	Character &c;

	public:
		View(Character &c);
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
	std::vector<Player> player_vector;

	public:
		// recebe uma View para garantir que já tenhamos chamado SDL_Init()
		Input(const View &v);

		void refresh();
		bool should_quit() { return m_should_quit; }
		bool movement(int direction);
};
