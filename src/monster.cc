#include "general_func.h"
#include "models.h"
#include "view.h"

Monster::Monster(float x, float y, int size, float height, float width)
	: x(x), y(y), size(size), height(height), width(width), center_x(x),
	  center_y(y)
{
	calc_bordas(l, r, x, y, height, width);
}

void Monster_vector::add_monster(Monster &element)
{
	enemy_vector.push_back(element);
}

void Monster_vector::delete_monster(int pos)
{
	enemy_vector.erase(enemy_vector.begin() + (pos - 1));
}

void insert_Monster(Monster &m, Monster_vector &mv)
{
	mv.add_monster(m);
}
