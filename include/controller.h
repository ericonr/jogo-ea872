#pragma once

#include "models.h"
#include "view.h"

class Controller {
	Characters &chars;
	Scenary_element_vector &sev;

	public:
		Controller(Characters &chars, Scenary_element_vector &sev): chars(chars),sev(sev) {}
		void update(Input &in, float t);
		
};
