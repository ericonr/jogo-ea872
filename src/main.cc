#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>

#include "json.hpp"

#include "controller.h"
#include "general_func.h"
#include "json.h"
#include "models.h"
#include "view.h"

static const int CONN_PORT = 9001, IN_PORT = 9002;

static const float T = 0.01;
const std::chrono::duration<int, std::milli> wait_time{10};

static void receive_data_package(PlayerMap &pm, JsonSender &js, std::mutex &mtx)
{
	JsonReceiver jr{IN_PORT};
	boost::asio::ip::udp::udp::endpoint endpoint;
	nlohmann::json ij;
	while (true) {
		jr.receive(ij, endpoint);

		mtx.lock();
		if (pm.update_player(ij, endpoint)) {
			endpoint.port(CONN_PORT);
			js.endpoints.push_back(endpoint);
		}
		mtx.unlock();
	}
}

static void run_game(Controller &c, JsonView &jv, PlayerMap &pm)
{
	JsonSender js;
	nlohmann::json j;

	std::mutex run_mtx;
	std::thread t(receive_data_package, std::ref(pm), std::ref(js), std::ref(run_mtx));

	while (true) {
		auto tp = std::chrono::steady_clock::now() + wait_time;

		run_mtx.lock();
		c.update(pm, T);
		jv.write(j);
		js.send(j);
		run_mtx.unlock();

		std::this_thread::sleep_until(tp);
	}
}

static void receive_view(JsonSwitcher &jsw)
{
	JsonReceiver jr{CONN_PORT};
	while (true) {
		jr.receive(jsw.for_write());
	}
}

static void view_game(View &v, Input &in, JsonView &jv, const char *ip)
{
	JsonSender js;
	js.add_endpoint(ip, IN_PORT);
	nlohmann::json ij;

	JsonSwitcher jsw;

	std::thread t(receive_view, std::ref(jsw));

	while (!in.should_quit()) {
		auto tp = std::chrono::steady_clock::now() + wait_time;
		in.refresh();
		in.to_json(ij);
		js.send(ij);

		auto j = jsw.for_read();
		jv.read(j);
		jsw.release_read();

		v.render();

		std::this_thread::sleep_until(tp); // também funciona sem
	}
	std::cout << "quitting!" << std::endl;
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
