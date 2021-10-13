#pragma once

#include "models.h"
#include "view.h"

class Controller {
	Characters &chars;
	Scenary_element_vector &sev;
	Monster_vector &mv;
	float time_elapsed = 0;

	public:
		Controller(Characters &chars, Scenary_element_vector &sev, Monster_vector &mv): chars(chars),sev(sev), mv(mv) {}
		void update(Input &in, float t);
		
};
