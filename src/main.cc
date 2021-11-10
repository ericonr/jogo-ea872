#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <mutex>          
#include "json.hpp"
#include "controller.h"
#include "general_func.h"
#include "json.h"
#include "models.h"
#include "view.h"

std::mutex mtx;  

static const int CONN_PORT = 9001, IN_PORT = 9002;

static const float T = 0.01;

static void receive_data_package(JsonReceiver &jr,PlayerMap &pm) {

	boost::asio::ip::udp::udp::endpoint endpoint;
	nlohmann::json ij;
	while(true) {
	
	jr.receive(ij, endpoint);
	mtx.lock();
	pm.update_player(ij, endpoint);
	mtx.unlock();
	std::cout << " teste" << std::endl;
	}
	

}





static void run_game(Controller &c, JsonView &jv, PlayerMap &pm,JsonReceiver &jr)
{
	JsonSender js;
	js.add_endpoint("127.0.0.1", CONN_PORT);
	
	nlohmann::json j;

	const std::chrono::duration<int, std::milli> t{10};
	std::chrono::steady_clock::time_point tp;
	
	auto t1 = std::thread(receive_data_package,std::ref(jr),std::ref(pm));
	

	while (1) {
		
		tp = std::chrono::steady_clock::now() + t;
		//receive_data_package(jr,pm);
		mtx.lock();
		c.update(pm, T);
		mtx.unlock();
		
		jv.write(j);
		js.send(j);
		std::this_thread::sleep_until(tp);
	}
}

static void view_game(View &v, Input &in, JsonView &jv)
{
	JsonSender js;
	js.add_endpoint("127.0.0.1", IN_PORT);
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
		JsonReceiver jr{IN_PORT};
		
		
		run_game(control, jv, pm, jr);
	} else {
		View v{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis};
		Input in{v};
		view_game(v, in, jv);
	}
}
