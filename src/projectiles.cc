#include <vector>

#include "models.h"
#include "view.h"
#include "general_func.h"

Character_projectile::Character_projectile(Character &c):c(c){}

void Character_projectile::sum_id_counter() {
    id_counter += 1;

}

void Character_projectile::fire_new_projectile(int direction) {
    
    Individual_projectile base_projectile;
    base_projectile.x = c.x;
    base_projectile.y = c.y;
    base_projectile.id = id_counter;
    base_projectile.direction = direction;
    sum_id_counter();

    character_individual_projectile.push_back(base_projectile);
}

void Character_projectile::delete_projectile(int id){
    
    int search_id;
    for(unsigned n_projectile = 0; n_projectile < character_individual_projectile.size(); n_projectile++) {
        search_id = character_individual_projectile[n_projectile].id;
        if(search_id == id) {
            character_individual_projectile.erase(character_individual_projectile.begin() + (n_projectile));

        } 
    }
}

void Character_projectile_vector::add_projectile_vector(Character_projectile *cp)
{
    all_projectile_vector.push_back(cp);
}
