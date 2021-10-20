#pragma once
#include "json.hpp"
#include <iostream>
#include <vector>

#define MONSTER_OSC_AMP 5
#define MONSTER_OSC_FREQ 1
#define PI 3.14159265

namespace direction
{
const int up = 0, down = 1, left = 2, right = 3;
const int max = 5;
} // namespace direction

struct Space_point {
	float x;
	float y;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Space_point, x, y);
};

class Character
{
	public:
	float x, y;
	float last_shot_time;

	Space_point l, r;
	int size;
	float height, width;
	unsigned long id;
	int last_direction;

	Character()
	{
	}
	Character(float x, float y, int size, float height, float width);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Character, x, y, last_shot_time, l, r, size, height, width, id, last_direction);
};

class Characters
{
	public:
	std::vector<Character> Character_vector;

	void add_character(Character &c);
	void delete_character(int pos);
};

class Scenery_element
{
	public:
	float x, y;
	int size;
	float height, width;
	enum { tree, rock } type;
	Space_point l, r;

	Scenery_element()
	{
	}
	Scenery_element(float x, float y, int size, float height, float width);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Scenery_element, x, y, size, height, width, type, l, r);
};

class Scenery_element_vector
{

	public:
	std::vector<Scenery_element> element_vector;

	Scenery_element_vector()
	{
	}

	void add_element(Scenery_element &element);
};

class Monster
{
	public:
	float x, y;
	int size;
	float height, width;
	Space_point l, r;
	float center_x;
	float center_y;
	unsigned long id;

	Monster()
	{
	}
	Monster(float x, float y, int size, float height, float width);
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Monster, x, y, size, height, width, l, r, center_x, center_y, id);
};

class Monster_vector
{
	public:
	std::vector<Monster> enemy_vector;

	Monster_vector()
	{
	}

	void add_monster(Monster &element);
	void delete_monster(int pos);
};

struct Individual_projectile {
	float x;
	float y;
	int direction;
	size_t id;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Individual_projectile, x, y, direction, id);
};

class Projectile_vector
{
	public:
	std::vector<Individual_projectile> all_projectile_vector;

	Projectile_vector(){};

	void fire_new_projectile(const Character &c);
	void delete_projectile(size_t id);
};

struct Time_counter {
	float time_elapsed = 0;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Time_counter, time_elapsed);
};
