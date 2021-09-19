#include <iostream>

#include "models.h"
#include "controller.h"
#include "view.h"

static const float T = 0.01;

int main(int argc, char **argv)
{
	Character c{0, 0};
	Controller co{c};
	View v{c};
	Input in{v};

	while(!in.should_quit()) {
		v.render();
		in.refresh();
		co.update(in, T);
		v.delay(T);
	}
}
