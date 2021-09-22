#include <stdexcept>
#include <iostream>

#include "view.h"

Input::Input(const View &v):
	m_should_quit(false),
	player_vector(0)
{
	
	keyboard = SDL_GetKeyboardState(&numkeys);
}

void Input::refresh()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_should_quit = true;
		}
	}

	if (keyboard[SDL_SCANCODE_Q]) m_should_quit = true;

	for (auto &p: player_vector) {
		if (p.type == Player::keyboard) {
			int i = 0;
			p.movement = 0;
			for (auto key: p.keys) {
				p.movement |= keyboard[key] << i++;
			}
		}
	}
}

bool Input::movement(int direction, unsigned int n_player)
{
	if (direction >= direction::max) throw std::logic_error("out of bounds index");
	return player_vector[n_player].movement & (1 << direction);
}
