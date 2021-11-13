#include <stdexcept>

#include "controller.h"

// essa função automaticamente adiciona um player e o personagem associado,
// se ainda não houver um
int PlayerMap::update_player(const nlohmann::json &j, const boost::asio::ip::udp::udp::endpoint &e)
{
	int rv = 0;

	std::string s = e.address().to_string();
	Player *p = nullptr;
	try {
		p = &players.at(s);
	} catch (std::out_of_range &oor) {
		// criar jogador
		rv = 1;

		std::cout << "adicionando jogador " << s << std::endl;
		p = &players[s];
		p->pos = chars.Character_vector.size();

		Character c{0, 0, 50, 5, 5};
		chars.Character_vector.push_back(c);
	}

	j.at("mov").get_to(p->mov);

	return rv;
}
