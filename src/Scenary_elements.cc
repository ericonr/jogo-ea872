#include "general_func.h"
#include "models.h"

Scenery_element::Scenery_element(float x, float y, int size, float height,
								 float width)
	: x(x), y(y), size(size), height(height), width(width), type(rock)
{
	calc_bordas(l, r, x, y, height, width);
}

void Scenery_element_vector::add_element(Scenery_element &element)
{
	element_vector.push_back(element);
}

void insert_Scenery_element(Scenery_element &e, Scenery_element_vector &sev)
{
	sev.add_element(e);
}
