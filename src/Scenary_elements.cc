
#include "models.h"

void Scenery_element_vector::add_element(Scenery_element &element)
{

	element_vector.push_back(element);
}

void Scenery_element_vector::delete_element(int pos)
{

	element_vector.erase(element_vector.begin() + (pos - 1));
}

void insert_Scenery_element(Scenery_element &e, Scenery_element_vector &sev)
{
	sev.add_element(e);
}


void Scenery_element::calc_bordas_() {
	
	l.x = x - (width / 2);
	l.y = y + (height / 2);
	r.x = x + (width / 2);
	r.y = y - (height / 2);

}