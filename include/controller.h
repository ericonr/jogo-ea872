#pragma once

#include <unordered_map>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "json.hpp"

#include "models.h"
#include "view.h"

struct Player {
	size_t pos;
	unsigned mov;
};

class PlayerMap
{
	Characters &chars;

	public:
	std::unordered_map<std::string, Player> players;

	PlayerMap(Characters &chars) : chars(chars)
	{
	}

	void update_player(const nlohmann::json &j, const boost::asio::ip::udp::udp::endpoint &e);
};

class Controller
{
	Characters &chars;
	Scenery_element_vector &sev;
	Monster_vector &mv;
	Projectile_vector &pv;
	Time_counter &tc;

	public:
	Controller(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv,
			   Time_counter &tc)
		: chars(chars), sev(sev), mv(mv), pv(pv), tc(tc)
	{
	}
	void update(Input &in, float t);
};
