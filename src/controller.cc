#include "controller.h"

// 20 km/h = 72 m/s
static const float max_speed = 72.;

static const float sqrtof2 = 1.41421356;

void Controller::update(Input &in, float t)
{
	float dx = 0., dy = 0.;
	if (in.movement(direction::up)) dy += max_speed * t;
	if (in.movement(direction::down)) dy -= max_speed * t;
	if (in.movement(direction::left)) dx -= max_speed * t;
	if (in.movement(direction::right)) dx += max_speed * t;

	// módulo da velocidade = max_speed
	if (dx != 0 && dy != 0) {
		dx /= sqrtof2;
		dy /= sqrtof2;
	}

	c.x += dx;
	c.y += dy;
}
