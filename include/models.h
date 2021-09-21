#pragma once

#include <vector>

class Character {
	public:
		float x, y;
		int size;
		unsigned long id;
		Character(float x, float y, int size): x(x), y(y), size(size) {}
};

class Characters {
	public:
		std::vector<Character> Character_vector;
		void add_character(Character &c);
		void delete_character(Character &c);
		Characters();

};
