#include <fstream>
#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "json.hpp"

#include "controller.h"
#include "general_func.h"
#include "json.h"
#include "models.h"
#include "view.h"

static const float T = 0.01;

static void run_game(Controller &c, View &v, Input &in, JsonSender &js)
{
	while (!in.should_quit()) {
		v.render();
		in.refresh();
		c.update(in, T);
		js.send();
		v.delay(T);
	}
}

static void view_game(View &v, Input &in, JsonView &jv)
{
	char message[64000];
	boost::asio::io_service my_io_service;
	boost::asio::ip::udp::udp::endpoint local_endpoint(boost::asio::ip::udp::udp::v4(), 9001);
	boost::asio::ip::udp::udp::socket my_socket(my_io_service, local_endpoint);
	boost::asio::ip::udp::udp::endpoint remote_endpoint;

	while (!in.should_quit()) {
		size_t len = my_socket.receive_from(boost::asio::buffer(message, sizeof message), remote_endpoint);
		message[len] = 0;
		std::cout << message << std::endl;
		nlohmann::json j = nlohmann::json::parse(message);
		jv.read(j);
		v.render();
		in.refresh();
	}
}

int main(int argc, char **argv)
{
	Characters vetor_personagem;
	Scenery_element_vector vetor_elementos;
	Monster_vector vetor_monstros;
	Projectile_vector vetor_projeteis;
	Time_counter tc;

	View v{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis};
	JsonView jv{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis, tc};
	Input in{v};
	Controller control{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis, tc};

	if (argc == 1) {
		Monster m0{-15, 10, 50, 5, 5};
		Monster m1{15, 15, 50, 5, 5};
		vetor_monstros.add_monster(m0);
		vetor_monstros.add_monster(m1);

		Scenery_element e1{10, 10, 50, 5, 5};
		Scenery_element e2{-10, -10, 50, 5, 5};
		vetor_elementos.add_element(e1);
		vetor_elementos.add_element(e2);

		JsonSender js{jv};

		boost::asio::ip::address ip_remoto = boost::asio::ip::address::from_string("127.0.0.1");
		boost::asio::ip::udp::udp::endpoint remote_endpoint(ip_remoto, 9001);
		js.endpoints.push_back(remote_endpoint);

		run_game(control, v, in, js);

		nlohmann::json j;
		std::ofstream f{"save_game.json"};
		jv.write(j);
		f << j;

		std::cout << j << std::endl;
	} else {
		view_game(v, in, jv);
	}
}
