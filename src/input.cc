#include <stdexcept>

#include "view.h"

Input::Input(const View &v):
	m_should_quit(false),
	player_vector(0)
{
	Player p{0, 0, Player::keyboard, {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D}};
	player_vector.push_back(p);

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

bool Input::movement(int direction)
{
	if (direction >= direction::max) throw std::logic_error("out of bounds index");
	return player_vector[0].movement & (1 << direction);
}
