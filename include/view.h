#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "models.h"

class View {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture, *bg;
	SDL_Rect target;
	Character &c;

	public:
		View(Character &c);
		~View();

		void render();
		void delay(float t);
};

class Input {
	SDL_Event event;
	const Uint8 *keyboard;

	bool m_should_quit;

	public:
		// recebe uma View para garantir que já tenhamos chamado SDL_Init()
		Input(const View &v);

		void refresh();
		bool should_quit() { return m_should_quit; }
};