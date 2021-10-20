#pragma once
#include "models.h"
#include "view.h"

void insert_playable_character(Character &c, Player &p, Input &in, Characters &chars);
void insert_Scenery_element(Scenery_element &e, Scenery_element_vector &sev);
void insert_Monster(Monster &m, Monster_vector &mv);

void calc_bordas(Space_point &l, Space_point &r, float x, float y, float height, float width);
