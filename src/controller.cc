#include "controller.h"
#include "general_func.h"
#include "models.h"
#include <algorithm>
#include <math.h>
#include <vector>

// 20 km/h = 72 m/s
static const float max_speed = 72.;

static const float projectile_speed = 90;

static const float sqrtof2 = 1.41421356;

static const float projectile_height = 5.0;
static const float projectile_width = 5.0;

static const float negative_boad_limit_x = -100;
static const float positive_boad_limit_x = 100;

static const float negative_boad_limit_y = -100;
static const float positive_boad_limit_y = 100;

bool doOverlap(Space_point l1, Space_point r1, Space_point l2, Space_point r2)
{

	// To check if either rectangle is actually a line
	// For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}
	// r2={0,1}

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y) {
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x) return false;

	// If one rectangle is above other
	if (r1.y >= l2.y || r2.y >= l1.y) return false;

	return true;
}

static bool is_direction(unsigned mov, unsigned direction)
{
	return mov & (1 << direction);
}

void Controller::update(const PlayerMap &pm, float t)
{
	for (const auto &player : pm.players) {
		unsigned mov = player.second.mov;
		auto &c = chars.Character_vector[player.second.pos];
		float dx = 0., dy = 0.;
		int direction = -1;
		if (is_direction(mov, direction::up)) {
			dy += max_speed * t;
			direction = direction::up;
		}
		if (is_direction(mov, direction::down)) {
			dy -= max_speed * t;
			direction = direction::down;
		}
		if (is_direction(mov, direction::left)) {
			dx -= max_speed * t;
			direction = direction::left;
		}
		if (is_direction(mov, direction::right)) {
			dx += max_speed * t;
			direction = direction::right;
		}

		if (direction != -1) c.last_direction = direction;

		// módulo da velocidade = max_speed
		if (dx != 0 && dy != 0) {
			dx /= sqrtof2;
			dy /= sqrtof2;
		}

		// esperar ter se movido em alguma direção
		if (tc.time_elapsed - c.last_shot_time >= 1.f && c.last_direction != -1) {
			c.last_shot_time = tc.time_elapsed;
			pv.fire_new_projectile(c);
		}

		bool collision_flag = false;
		Space_point comparison_value_l;
		Space_point comparison_value_r;

		comparison_value_l.x = dx + c.x - ((c.width) / 2);
		comparison_value_l.y = dy + c.y + ((c.height) / 2);
		comparison_value_r.x = dx + c.x + ((c.width) / 2);
		comparison_value_r.y = dy + c.y - ((c.height) / 2);

		for (unsigned n_element = 0; n_element < sev.element_vector.size(); n_element++) {
			collision_flag = doOverlap(comparison_value_l, comparison_value_r, sev.element_vector[n_element].l,
									   sev.element_vector[n_element].r);

			if (collision_flag == true) {
				break;
			}
		}

		if (collision_flag == false) {
			c.x += dx;
			c.y += dy;

			c.l = comparison_value_l;
			c.r = comparison_value_r;
		}
	}

	for (unsigned n_monsters = 0; n_monsters < mv.enemy_vector.size(); n_monsters++) {
		mv.enemy_vector[n_monsters].x =
			mv.enemy_vector[n_monsters].center_x + (MONSTER_OSC_AMP * cos(2 * PI * MONSTER_OSC_FREQ * tc.time_elapsed));
	}

	std::vector<size_t> to_delete;
	for (auto &p : pv.all_projectile_vector) {
		float dx = 0, dy = 0;
		Space_point Projectile_hit_l;
		Space_point Projectile_hit_r;

		// deleta quando sai da tela
		if (p.x < negative_boad_limit_x || p.x > positive_boad_limit_x || p.y < negative_boad_limit_y ||
			p.y > positive_boad_limit_y) {

			to_delete.push_back(p.id);
			continue;
		}

		Projectile_hit_l.x = p.x - (projectile_width / 2);
		Projectile_hit_l.y = p.y + (projectile_height / 2);

		Projectile_hit_r.x = p.x + (projectile_width / 2);
		Projectile_hit_l.y = p.y - (projectile_height / 2);

		if (p.direction == direction::up) dy = projectile_speed;
		if (p.direction == direction::down) dy = -projectile_speed;
		if (p.direction == direction::left) dx = -projectile_speed;
		if (p.direction == direction::right) dx = projectile_speed;
		p.x += dx * t;
		p.y += dy * t;
		bool Projectile_hit_flag = false;
		for (auto &m : mv.enemy_vector) {

			// deleta projetil na colisao
			Projectile_hit_flag = doOverlap(Projectile_hit_l, Projectile_hit_r, m.l, m.r);
			if (Projectile_hit_flag == true) {
				to_delete.push_back(p.id);
				continue;
			}
		}
	}
	std::reverse(to_delete.begin(), to_delete.end());
	for (auto n : to_delete) {
		// pv.delete_projectile(n);
	}

	tc.time_elapsed += t;
}
