#pragma once
#include <vector>
#include <iostream>

#define MONSTER_OSC_AMP 5
#define MONSTER_OSC_FREQ 1
#define PI 3.14159265

namespace direction {
	const int up = 0, down = 1, left = 2, right = 3;
	const int max = 5;
}

struct Space_point {
	float x;
	float y;
};

class Character {
	public:
		float x, y;
		float last_shot_time;
	
		Character(float x, float y, int size, float height, float width);

		Space_point l,r;
		int size;
		float height,width;
		unsigned long id;
		int last_direction;
};

class Characters {
	public:
		std::vector<Character> Character_vector;

		Characters() {}

		void add_character(Character &c);
		void delete_character(int pos);
};

class Scenary_element{
	public:
		float x,y;
		int size;
		float height,width;
		enum {tree, rock} type;
		unsigned long id;
		Space_point l,r;
		
		Scenary_element(float x, float y, int size, float height, float width): x(x), y(y), size(size), height(height),width(width) {
		  
		  	l.x = x - (width/2);
    		l.y = y + (height/2);
  	  		r.x = x + (width/2);
    		r.y = y - (height/2);
			
		}	



};

class Scenary_element_vector {
	
	public:
		std::vector<Scenary_element> element_vector;

		Scenary_element_vector() {}

		void add_element(Scenary_element &element);
		void delete_element(int pos);


};


class Monster {
	
	public:
		
		float x, y;
		int size;
		float height,width;
		Space_point l,r;
		float center_x;
		float center_y;
		unsigned long id;
		
		Monster(float x, float y, int size, float height, float width): x(x), y(y), size(size), height(height),width(width) {
		  
		  	l.x = x - (width/2);
    		l.y = y + (height/2);
  	  		r.x = x + (width/2);
    		r.y = y - (height/2);

			center_x = x;
			center_y = y;
			
		}	
};

class Monster_vector {
	public:
		std::vector <Monster> enemy_vector;

		Monster_vector() {}

		void add_monster(Monster &element);
		void delete_monster(int pos);
};


struct Individual_projectile {
	float x;
	float y;
	int direction;
};

class Projectile_vector {
	public:
		std::vector <Individual_projectile> all_projectile_vector;

		Projectile_vector() {};

		void fire_new_projectile(const Character &c);
		void delete_projectile(unsigned id);
};
