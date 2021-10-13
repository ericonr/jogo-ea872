#pragma once

#include "models.h"
#include "view.h"

class Controller {
	Characters &chars;
	Scenery_element_vector &sev;
	Monster_vector &mv;
	Projectile_vector &pv;
	float time_elapsed = 0;

	public:
		Controller(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv):
				chars(chars),sev(sev), mv(mv), pv(pv) {}
		void update(Input &in, float t);
		
};
