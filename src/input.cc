#include <iostream>
#include <stdexcept>

#include "view.h"

Input::Input(const View &v) : m_should_quit(false)
{
	keyboard = SDL_GetKeyboardState(&numkeys);
}

static int keys[4] = {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D};

void Input::refresh()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_should_quit = true;
		}
	}

	if (keyboard[SDL_SCANCODE_Q]) m_should_quit = true;

	m_movement = 0;
	unsigned i = 0;
	for (auto key : keys) {
		m_movement |= keyboard[key] << i++;
	}
}

void Input::to_json(nlohmann::json &j)
{
	j["mov"] = m_movement;
}
