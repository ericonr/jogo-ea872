#include "view.h"

Input::Input(const View &v):
	m_should_quit(false)
{
	keyboard = SDL_GetKeyboardState(nullptr);
}

void Input::refresh()
{
	SDL_PumpEvents();
	if (keyboard[SDL_SCANCODE_Q]) m_should_quit = true;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_should_quit = true;
		}
	}
}
