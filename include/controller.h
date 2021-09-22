#pragma once

#include "models.h"
#include "view.h"

class Controller {
	Characters &chars;

	public:
		Controller(Characters &chars): chars(chars) {}
		void update(Input &in, float t);
};
