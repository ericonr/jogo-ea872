#include "controller.h"
#include "models.h"
#include <math.h>  


// 20 km/h = 72 m/s
static const float max_speed = 72.;

static const float sqrtof2 = 1.41421356;



bool doOverlap(Space_point l1, Space_point r1, Space_point l2,Space_point r2)
{
 
    // To check if either rectangle is actually a line
    // For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}
    // r2={0,1}
 
    if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
        || l2.y == r2.y) {
        // the line cannot have positive overlap
        return false;
    }
 
    // If one rectangle is on left side of other
    if (l1.x >= r2.x || l2.x >= r1.x)
        return false;
 
    // If one rectangle is above other
    if (r1.y >= l2.y || r2.y >= l1.y)
        return false;
 
    return true;
}
 
 

void Controller::update(Input &in, float t)
{
	for(unsigned n_player = 0; n_player < chars.Character_vector.size(); n_player++){
		
		float dx = 0., dy = 0.;
		if (in.movement(direction::up, n_player)) dy += max_speed * t;
		if (in.movement(direction::down, n_player)) dy -= max_speed * t;
		if (in.movement(direction::left, n_player)) dx -= max_speed * t;
		if (in.movement(direction::right, n_player)) dx += max_speed * t;

		// módulo da velocidade = max_speed
		if (dx != 0 && dy != 0) {
			dx /= sqrtof2;
			dy /= sqrtof2;
		}

		if (time_elapsed - pv.all_projectile_vector[n_player]->last_shot_time >= 1.f) {
			int direction = -1;
			if (in.movement(direction::up, n_player)) direction = direction::up;
			else if (in.movement(direction::down, n_player)) direction = direction::down;
			else if (in.movement(direction::left, n_player)) direction = direction::left;
			else if (in.movement(direction::right, n_player)) direction = direction::right;

			// só atira se estiver se movendo
			if (direction != -1) {
				std::cout << "atirando\n";
				pv.all_projectile_vector[n_player]->last_shot_time = time_elapsed;
				pv.all_projectile_vector[n_player]->fire_new_projectile(direction);
			}
		}

		bool collision_flag = false;
		Space_point comparison_value_l;
		Space_point comparison_value_r;
		
		comparison_value_l.x = dx + chars.Character_vector[n_player].x - ((chars.Character_vector[n_player].width)/2);
		comparison_value_l.y= dy +chars.Character_vector[n_player].y + ((chars.Character_vector[n_player].height)/2);
		comparison_value_r.x = dx +chars.Character_vector[n_player].x + ((chars.Character_vector[n_player].width)/2);
		comparison_value_r.y = dy +chars.Character_vector[n_player].y - ((chars.Character_vector[n_player].height)/2);
		
		for(unsigned n_element = 0; n_element < sev.element_vector.size(); n_element++) {
			
			collision_flag = doOverlap(comparison_value_l,comparison_value_r
			,sev.element_vector[n_element].l,sev.element_vector[n_element].r);

			if(collision_flag == true) {
				break;
			}
		}

		if(collision_flag == false) {
			chars.Character_vector[n_player].x+= dx;
			chars.Character_vector[n_player].y+= dy;

			chars.Character_vector[n_player].l = comparison_value_l;
			chars.Character_vector[n_player].r = comparison_value_r;
		}

		/*std::cout <<"posição em rx do player "<< n_player << "\r\n" << chars.Character_vector[n_player].r.x<< "\r\n" ;
		std::cout <<"posição em ry do player "<< n_player << "\r\n" << chars.Character_vector[n_player].r.y<< "\r\n" ;
		std::cout <<"posição em lx do player "<< n_player << "\r\n" << chars.Character_vector[n_player].l.x<< "\r\n" ;
		std::cout <<"posição em ly do player "<< n_player << "\r\n" << chars.Character_vector[n_player].l.y<< "\r\n" ;
		*/
	}

	for(unsigned n_monsters = 0; n_monsters < mv.enemy_vector.size();n_monsters++){

		mv.enemy_vector[n_monsters].x = mv.enemy_vector[n_monsters].center_x + (MONSTER_OSC_AMP *cos(2 * PI * MONSTER_OSC_FREQ * time_elapsed));
		//std::cout <<"posição em x do monstro "<< n_monsters << "\r\n" << mv.enemy_vector[n_monsters].x << "\r\n" ;
	}

	for (auto &projetil: pv.all_projectile_vector) {
		for (auto &p: projetil->character_individual_projectile) {
			float dx=0, dy=0;
			float speed = 30;
			if (p.direction == direction::up) dy=speed;
			if (p.direction == direction::down) dy=-speed;
			if (p.direction == direction::left) dx=-speed;
			if (p.direction == direction::right) dx=speed;
			p.x += dx*t;
			p.y += dy*t;
		}
	}

	time_elapsed += t;
}

