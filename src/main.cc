#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#include "json.hpp"

#include "controller.h"
#include "general_func.h"
#include "json.h"
#include "models.h"
#include "view.h"

static const int CONN_PORT = 9001, IN_PORT = 9002;

static const float T = 0.01;

static void run_game(Controller &c, JsonView &jv, PlayerMap &pm)
{
	JsonSender js;
	JsonReceiver jr{IN_PORT};
	nlohmann::json j, ij;

	boost::asio::ip::udp::udp::endpoint endpoint;

	const std::chrono::duration<int, std::milli> t{10};
	std::chrono::steady_clock::time_point tp;
	while (1) {
		tp = std::chrono::steady_clock::now() + t;

		jr.receive(ij, endpoint);
		if (pm.update_player(ij, endpoint)) {
			endpoint.port(CONN_PORT);
			js.endpoints.push_back(endpoint);
		}

		c.update(pm, T);
		jv.write(j);
		js.send(j);
		std::this_thread::sleep_until(tp);
	}
}

static void view_game(View &v, Input &in, JsonView &jv, const char *ip)
{
	JsonSender js;
	js.add_endpoint(ip, IN_PORT);
	JsonReceiver jr{CONN_PORT};
	nlohmann::json j, ij;

	while (!in.should_quit()) {
		in.refresh();
		in.to_json(ij);
		js.send(ij);
		jr.receive(j);
		jv.read(j);
		v.render();
	}
}

int main(int argc, char **argv)
{
	Characters vetor_personagem;
	Scenery_element_vector vetor_elementos;
	Monster_vector vetor_monstros;
	Projectile_vector vetor_projeteis;
	Time_counter tc;

	JsonView jv{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis, tc};

	if (argc == 1) {
		Monster m0{-15, 10, 50, 5, 5};
		Monster m1{15, 15, 50, 5, 5};
		vetor_monstros.add_monster(m0);
		vetor_monstros.add_monster(m1);

		Scenery_element e1{10, 10, 50, 5, 5};
		Scenery_element e2{-10, -10, 50, 5, 5};
		vetor_elementos.add_element(e1);
		vetor_elementos.add_element(e2);

		Controller control{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis, tc};
		PlayerMap pm{vetor_personagem};

		run_game(control, jv, pm);
	} else {
		View v{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis};
		Input in{v};
		view_game(v, in, jv, argv[1]);
	}
}
