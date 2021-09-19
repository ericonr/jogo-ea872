#pragma once

#include "models.h"
#include "view.h"

class Controller {
	Character &c;

	public:
		Controller(Character &c): c(c) {}

		void update(Input &in, float t);
};
