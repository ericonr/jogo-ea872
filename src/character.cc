#include "general_func.h"
#include "models.h"
#include "view.h"

Character::Character(float x, float y, int size, float height, float width)
	: x(x), y(y), size(size), height(height), width(width), last_direction(-1)
{
	calc_bordas(l, r, x, y, height, width);
}

void Characters::add_character(Character &c)
{
	Character_vector.push_back(c);
	// c.id = (Character_vector.size())- 1;
}

void Characters::delete_character(int pos)
{
	Character_vector.erase(Character_vector.begin() + (pos - 1));
}

void Input::add_player(Player &p)
{
	player_vector.push_back(p);
}

void Input::delete_player(int pos)
{
	player_vector.erase(player_vector.begin() + (pos - 1));
}

void insert_playable_character(Character &c, Player &p, Input &in,
							   Characters &chars)
{
	chars.add_character(c);
	in.add_player(p);
}

void calc_bordas(Space_point &l, Space_point &r, float x, float y, float height,
				 float width)
{
	l.x = x - (width / 2);
	l.y = y + (height / 2);
	r.x = x + (width / 2);
	r.y = y - (height / 2);
}
