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

void JsonSender::add_endpoint(const char *ip, int port)
{
	boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string(ip);
	boost::asio::ip::udp::udp::endpoint remote_endpoint(ip_remoto, port);
	endpoints.push_back(remote_endpoint);
}

void JsonSender::send(const nlohmann::json &j)
{
	std::string message = j.dump();
	for (auto e : endpoints) {
		local_socket.send_to(boost::asio::buffer(message), e);
	}
}

void JsonReceiver::receive(nlohmann::json &j, boost::asio::ip::udp::udp::endpoint &e)
{
	size_t len = local_socket.receive_from(boost::asio::buffer(message, message.size()), e);
	message[len] = '\0';
	j = nlohmann::json::parse(message);
}

void JsonReceiver::receive(nlohmann::json &j)
{
	receive(j, remote_endpoint);
}
