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
	j.at("characters").get_to(chars.Character_vector);
	j.at("scenery").get_to(sev.element_vector);
	j.at("monsters").get_to(mv.enemy_vector);
	j.at("projectiles").get_to(pv.all_projectile_vector);
	j.at("time").get_to(tc);
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
