#include <mutex>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "json.hpp"
#include "models.h"
#include "view.h"

class JsonView
{
	Characters &chars;
	Scenery_element_vector &sev;
	Monster_vector &mv;
	Projectile_vector &pv;
	Time_counter &tc;

	public:
	JsonView(Characters &chars, Scenery_element_vector &sev, Monster_vector &mv, Projectile_vector &pv,
			 Time_counter &tc)
		: chars(chars), sev(sev), mv(mv), pv(pv), tc(tc)
	{
	}

	void write(nlohmann::json &j);
	void read(nlohmann::json const &j);
};

class JsonSender
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::udp::endpoint local_endpoint;
	boost::asio::ip::udp::udp::udp::socket local_socket;

	public:
	std::vector<boost::asio::ip::udp::udp::endpoint> endpoints;

	JsonSender(const char *ip)
		: local_endpoint(boost::asio::ip::address::from_string(ip), 0), local_socket(io_service, local_endpoint)
	{
	}

	void add_endpoint(const char *ip, int port);
	void send(const nlohmann::json &j);
};

class JsonReceiver
{
	boost::asio::io_service io_service;
	boost::asio::ip::udp::udp::endpoint local_endpoint;
	boost::asio::ip::udp::udp::udp::socket local_socket;

	boost::asio::ip::udp::udp::endpoint remote_endpoint;

	std::vector<unsigned char> message;

	public:
	JsonReceiver(const char *ip, int port)
		: local_endpoint(boost::asio::ip::address::from_string(ip), port), local_socket(io_service, local_endpoint),
		  message(64000)
	{
	}

	void receive(nlohmann::json &j, boost::asio::ip::udp::udp::endpoint &e);
	void receive(nlohmann::json &j);
};

class JsonSwitcher
{
	std::mutex mtx;
	int reader, writer;
	nlohmann::json j[2];

	public:
	JsonSwitcher() : reader(-1), writer(0)
	{
	}
	nlohmann::json &for_write();
	nlohmann::json &for_read();
	void release_read();
};
