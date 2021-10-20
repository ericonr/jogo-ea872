#include "general_func.h"
#include "models.h"
#include "view.h"

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

void Monster::calc_bordas_()
{

	l.x = x - (width / 2);
	l.y = y + (height / 2);
	r.x = x + (width / 2);
	r.y = y - (height / 2);

	center_x = x;
	center_y = y;
}