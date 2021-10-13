#include <iostream>

#include "models.h"
#include "controller.h"
#include "view.h"
#include "general_func.h"

static const float T = 0.01;

int main(int argc, char **argv)
{
	Character c0{0,0,50,5,5};
	Character c1{0,0,50,5,5};
	
	Monster m0{-15,10,50,5,5};
	Monster m1{15,15,50,5,5};

	Scenary_element e1 {10,10,50,5,5};
	Scenary_element e2 {-10,-10,50,5,5};

	Character_projectile cp0(c0);
	Character_projectile cp1(c1);

	Player p0{0, 0, Player::keyboard, {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D}};
	Player p1{0, 0, Player::keyboard, {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT}};

	Characters vetor_personagem;
	Scenary_element_vector vetor_elementos;
	Monster_vector vetor_monstros;
	Character_projectile_vector vetor_projeteis;
	View v{vetor_personagem,vetor_elementos,vetor_monstros,vetor_projeteis};
	Input in{v};

	insert_playable_character(c0,p0,in,vetor_personagem,&cp0,vetor_projeteis);
	insert_playable_character(c1,p1,in,vetor_personagem,&cp1,vetor_projeteis);
	insert_Scenary_element(e1,vetor_elementos);
	insert_Scenary_element(e2,vetor_elementos);
	insert_Monster(m0,vetor_monstros);
	insert_Monster(m1,vetor_monstros);

	Controller control{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis};

	while(!in.should_quit()) {
		v.render();
		in.refresh();
		control.update(in, T);
		v.delay(T);
	} 
}
