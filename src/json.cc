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
	try {
		j.at("characters").get_to(chars.Character_vector);
		j.at("scenery").get_to(sev.element_vector);
		j.at("monsters").get_to(mv.enemy_vector);
		j.at("projectiles").get_to(pv.all_projectile_vector);
		j.at("time").get_to(tc);
	} catch (...) {
		std::cout << "fixme - json bug!" << std::endl;
	}
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
	// std::cout << "len " << message.size() << std::endl;
	for (auto e : endpoints) {
		local_socket.send_to(boost::asio::buffer(message), e);
	}
}

void JsonReceiver::receive(nlohmann::json &j, boost::asio::ip::udp::udp::endpoint &e)
{
	size_t len = local_socket.receive_from(boost::asio::buffer(message, message.size() - 1), e);
	// std::cout << "rec " << len << std::endl;
	message[len] = '\0';
	j = nlohmann::json::parse(message);
}

void JsonReceiver::receive(nlohmann::json &j)
{
	receive(j, remote_endpoint);
}

nlohmann::json &JsonSwitcher::for_write()
{
	mtx.lock();
	if (reader != -1) {
		writer = !reader;
	} else {
		writer = !writer;
	}
	mtx.unlock();
	return j[writer];
}

nlohmann::json &JsonSwitcher::for_read()
{
	assert(reader == -1);

	mtx.lock();
	reader = !writer;
	mtx.unlock();
	return j[reader];
}

void JsonSwitcher::release_read()
{
	mtx.lock();
	reader = -1;
	mtx.unlock();
}
