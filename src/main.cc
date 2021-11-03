#include <fstream>
#include <iostream>

#include "json.hpp"

#include "controller.h"
#include "general_func.h"
#include "models.h"
#include "view.h"
#include <boost/asio.hpp>
#include <boost/bind.hpp>


static const float T = 0.01;

static void run_game(Controller &c, View &v, Input &in)
{
	while (!in.should_quit()) {
		v.render();
		in.refresh();
		c.update(in, T);
		v.delay(T);
	}
}

int main(int argc, char **argv)
{
	Player p0{0, 0, Player::keyboard, {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D}};
	Player p1{0, 0, Player::keyboard, {SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT}};

	Characters vetor_personagem;
	Scenery_element_vector vetor_elementos;
	Monster_vector vetor_monstros;
	Projectile_vector vetor_projeteis;
	Time_counter tc;

	View v{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis};
	Input in{v};
	Controller control{vetor_personagem, vetor_elementos, vetor_monstros, vetor_projeteis, tc};

	if (argc == 1) {
		Character c0{0, 0, 50, 5, 5};
		Character c1{0, 0, 50, 5, 5};

		Monster m0{-15, 10, 50, 5, 5};
		Monster m1{15, 15, 50, 5, 5};

		Scenery_element e1{10, 10, 50, 5, 5};
		Scenery_element e2{-10, -10, 50, 5, 5};

		insert_Scenery_element(e1, vetor_elementos);
		insert_Scenery_element(e2, vetor_elementos);
		insert_Monster(m0, vetor_monstros);
		insert_Monster(m1, vetor_monstros);

		insert_playable_character(c0, p0, in, vetor_personagem);
		insert_playable_character(c1, p1, in, vetor_personagem);

		run_game(control, v, in);

		nlohmann::json j;
		std::ofstream f{"save_game.json"};
		j["characters"] = vetor_personagem.Character_vector;
		j["scenery"] = vetor_elementos.element_vector;
		j["monsters"] = vetor_monstros.enemy_vector;
		j["projectiles"] = vetor_projeteis.all_projectile_vector;
		j["time"] = tc;
		f << j;

		std::string message = j.dump();
	

	  	boost::asio::io_service io_service;
	  	boost::asio::ip::udp::udp::endpoint local_endpoint(	boost::asio::ip::udp::udp::v4(), 0);
		boost::asio::ip::udp::udp::udp::socket meu_socket(io_service, local_endpoint);
		boost::asio::ip::address ip_remoto =
  		boost::asio::ip::address::from_string("127.0.0.1");

 		boost::asio::ip::udp::udp::endpoint remote_endpoint(ip_remoto, 9001);

  		meu_socket.send_to(boost::asio::buffer(message), remote_endpoint);
  
  		std::cout << message << std::endl;
 		std::cout << "Fim" << std::endl;
	
		
		


		
	} else {
		nlohmann::json j;
		std::ifstream f{"save_game.json"};
		f >> j;

		vetor_personagem.Character_vector = j["characters"].get<std::vector<Character>>();
		vetor_elementos.element_vector = j["scenery"].get<std::vector<Scenery_element>>();
		vetor_monstros.enemy_vector = j["monsters"].get<std::vector<Monster>>();
		vetor_projeteis.all_projectile_vector = j["projectiles"].get<std::vector<Individual_projectile>>();
		tc = j["time"].get<Time_counter>();

		in.add_player(p0);
		in.add_player(p1);

		run_game(control, v, in);
	}
}
