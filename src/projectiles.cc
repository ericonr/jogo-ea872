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
	base_projectile.id = id_counter;
	sum_id_counter();

	all_projectile_vector.push_back(base_projectile);
}

void Projectile_vector::delete_projectile(unsigned id)
{
	unsigned search_id;
	for (unsigned n_projectile = 0; n_projectile < all_projectile_vector.size();
		 n_projectile++) {
		search_id = all_projectile_vector[n_projectile].id;
		if (search_id == id) {
			all_projectile_vector.erase(all_projectile_vector.begin() +
										(n_projectile));
		}
	}
}

void Projectile_vector::sum_id_counter()
{
	id_counter += 1;
}
