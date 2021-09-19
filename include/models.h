#pragma once

class Character {
	public:
		float x, y;
		Character(float x, float y): x(x), y(y) {}
		int size;
		Character(float x, float y, int size): x(x), y(y), size(size) {}
};
