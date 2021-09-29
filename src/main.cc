#include <iostream>

#include "models.h"
#include "controller.h"
#include "view.h"
#include "general_func.h"

static const float T = 0.01;

int main(int argc, char **argv)
{
	Character c0{0, 0, 50,5,5};
	Character c1{0, 0, 50,5,5};
	Scenary_element e1 {10,10,50,5,5};
	Scenary_element e2 {-10,-10,50,5,5};

	Player p0{0, 0, Player::keyboard, {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D}};
	Player p1{0, 0, Player::keyboard, {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT}};



	Characters vetor_personagem;
	Scenary_element_vector vetor_elementos;
	View v{vetor_personagem,vetor_elementos};
	Input in{v};
	
	insert_playable_character(c0,p0,in,vetor_personagem);
	insert_playable_character(c1,p1,in,vetor_personagem);
	insert_Scenary_element(e1,vetor_elementos);
	insert_Scenary_element(e2,vetor_elementos);

	

	Controller control{vetor_personagem, vetor_elementos};
	

	while(!in.should_quit()) {
		v.render();
		in.refresh();
		control.update(in, T);
		v.delay(T);
	}
}
