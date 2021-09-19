#pragma once

#include <vector>

class Character {
	public:
		float x, y;
		int size;
		unsigned long id;
		Character(float x, float y, int size): x(x), y(y), size(size) {}
};

/*class Characters {
	unsigned long ids;

	public:
		std::vector<Character> cs;

		Characters(): cs(0) {}
		void add_character(Character &c);
};*/
