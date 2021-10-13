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
