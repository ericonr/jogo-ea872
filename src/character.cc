#include "models.h"


void Characters::add_character(Character &c)
{
    Character_vector.push_back(c);
	c.id = (Character_vector.size())- 1;
}

void Characters::delete_character(Character &c)
{
	Character_vector.pop_back();
}
