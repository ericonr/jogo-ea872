#include <vector>

#include "general_func.h"
#include "models.h"
#include "view.h"

void Projectile_vector::fire_new_projectile(const Character &c)
{
	Individual_projectile base_projectile;
	base_projectile.x = c.x;
	base_projectile.y = c.y;
	base_projectile.direction = c.last_direction;
	base_projectile.id = all_projectile_vector.size();

	all_projectile_vector.push_back(base_projectile);
}

void Projectile_vector::delete_projectile(size_t id)
{
	all_projectile_vector.erase(all_projectile_vector.begin() + id);
}
