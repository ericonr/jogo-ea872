#include <stdexcept>

#include "view.h"

Input::Input(const View &v):
	m_should_quit(false)
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

	m_should_quit = keyboard[SDL_SCANCODE_Q];
	m_movement[direction::up] = keyboard[SDL_SCANCODE_W];
	m_movement[direction::left] = keyboard[SDL_SCANCODE_A];
	m_movement[direction::down] = keyboard[SDL_SCANCODE_S];
	m_movement[direction::right] = keyboard[SDL_SCANCODE_D];
}

bool Input::movement(int direction)
{
	if (direction >= direction::max) throw std::logic_error("out of bounds index");
	return m_movement[direction];
}
