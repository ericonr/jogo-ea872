#pragma once
#include <vector>
#include <iostream>

struct Space_point {
	float x;
	float y;
};



class Character {
	public:
		float x, y;
		float height,width;
		Space_point l,r;
		int size;
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