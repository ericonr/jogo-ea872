#pragma once

#include "models.h"
#include "view.h"

class Controller
{
	Characters &chars;
	Scenery_element_vector &sev;
	Monster_vector &mv;
	Projectile_vector &pv;
	Time_counter &tc;

	public:
	Controller(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv, Time_counter &tc)
		: chars(chars), sev(sev), mv(mv), pv(pv), tc(tc)
	{
	}
	void update(Input &in, float t);
};
