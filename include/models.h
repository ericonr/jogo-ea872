#pragma once
#include <vector>
#include <iostream>

#define MONSTER_OSC_AMP 5
#define MONSTER_OSC_FREQ 1
#define PI 3.14159265

struct Space_point {
	float x;
	float y;
};


struct Individual_projectile {
	float x;
	float y;
	int id;
};


class Character {
	public:
		float x, y;
	
		Space_point l,r;
		int size;
		float height,width;
		unsigned long id;
		
		Character(float x, float y, int size, float height, float width): x(x), y(y), size(size), height(height),width(width) {
		  
		  	l.x = x - (width/2);
    		l.y = y + (height/2);
  	  		r.x = x + (width/2);
    		r.y = y - (height/2);
			
		}
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


class Character_projectile {
	public:
		std::vector<Individual_projectile> character_individual_projectile;
		Character &c;
		int id_counter;
		Character_projectile(Character &c);
		
		void fire_new_projectile();
		void delete_projectile(int id);
		void sum_id_counter();

};

class Character_projectile_vector {
	
	public:
		std::vector <Character_projectile> all_projectile_vector;

		Character_projectile_vector() {}

		void add_projectile_vector( Character_projectile &character_project);
		void delete_projectile_vector(int pos);


};