#include "json.h"

void JsonView::write(nlohmann::json &j)
{
	j["characters"] = chars.Character_vector;
	j["scenery"] = sev.element_vector;
	j["monsters"] = mv.enemy_vector;
	j["projectiles"] = pv.all_projectile_vector;
	j["time"] = tc;
}

void JsonView::read(nlohmann::json const &j)
{
	chars.Character_vector = j["characters"].get<std::vector<Character>>();
	sev.element_vector = j["scenery"].get<std::vector<Scenery_element>>();
	mv.enemy_vector = j["monsters"].get<std::vector<Monster>>();
	pv.all_projectile_vector = j["projectiles"].get<std::vector<Individual_projectile>>();
	tc = j["time"].get<Time_counter>();
}

void JsonSender::send()
{
	nlohmann::json j;
	jv.write(j);
	std::string message = j.dump();
	for (auto e : endpoints) {
		local_socket.send_to(boost::asio::buffer(message), e);
	}
}
