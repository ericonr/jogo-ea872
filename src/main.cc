#include <iostream>

#include "models.h"
#include "controller.h"
#include "view.h"

static const float T = 0.01;

int main(int argc, char **argv)
{
	Character c{0, 0, 50};
	Character c1{0, 0, 50};
	Characters vetor_personagem;
	vetor_personagem.add_character(c);
	vetor_personagem.add_character(c1);
	Controller control{vetor_personagem};
	View v{vetor_personagem};
	Input in{v};

	while(!in.should_quit()) {
		v.render();
		in.refresh();
		control.update(in, T);
		v.delay(T);
	}
	
}
