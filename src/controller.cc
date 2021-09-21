#include "controller.h"

// 20 km/h = 72 m/s
static const float max_speed = 72.;

static const float sqrtof2 = 1.41421356;

void Controller::update(Input &in, float t)
{

	for(unsigned int n_player = 0;n_player < chars.Character_vector.size();n_player++){
	
	float dx = 0., dy = 0.;
	if (in.movement(direction::up,n_player)) dy += max_speed * t;
	if (in.movement(direction::down,n_player)) dy -= max_speed * t;
	if (in.movement(direction::left,n_player)) dx -= max_speed * t;
	if (in.movement(direction::right,n_player)) dx += max_speed * t;

	// módulo da velocidade = max_speed
	if (dx != 0 && dy != 0) {
		dx /= sqrtof2;
		dy /= sqrtof2;
	}

	chars.Character_vector[n_player].x+= dx;
	chars.Character_vector[n_player].y+= dy;

	/*std::cout <<"posição em x do player "<< n_player << "\r\n" << chars.Character_vector[n_player].x<< "\r\n" ;
	std::cout <<"posição em y do player "<< n_player << "\r\n" << chars.Character_vector[n_player].y<< "\r\n" ;
	*/

	}
}


void Characters::add_character(Character &c){
	Character_vector.push_back(c);
	c.id = (Character_vector.size())- 1;
}

void Characters::delete_character(Character &c)
{
	Character_vector.pop_back();
}

