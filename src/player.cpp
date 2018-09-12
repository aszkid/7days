#include "player.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <spdlog/spdlog.h>

using nlohmann::json;


bool Player::from_json(Player *p, const jdm::path &file)
{
	auto log = spdlog::get("console");
	std::ifstream infile(file);
	if(!infile){
		log ->error("Failed to open player '{}'!", file);
		return false;
	}

	json j;
	infile >> j;

	p -> size.x = j["width"];
	p -> size.y = j["height"];
	p -> position.x = j["x"];
	p -> position.y = j["y"];
	
	const std::string player_texture = j["image"];
	if(!p -> texture.loadFromFile(file / ("../" + player_texture))) {
		//No se com funciona lo dels paths encara
		log -> error("Failed at loading player texture!");
	}
	
	return true;
}

bool Player::can_move(Player p, std::vector<CollisionRect> rect) // S'ha de passar la posició on estarà, no en la que esta
{
	sf::Vector2f px_cords(p.position.x, p.position.x + p.size.x);
	sf::Vector2f py_cords(p.position.y, p.position.y + p.size.y);
	sf::Vector2f bx_cords;
	sf::Vector2f by_cords;

	for(size_t i=0 ; i < rect.size(); i++ ){
		bx_cords.x = rect[i].pos.x;
		bx_cords.y = rect[i].pos.x + rect[i].size.x; 
		if(!dim1(px_cords, bx_cords)){
	                by_cords.x = rect[i].pos.y;
	                by_cords.y = rect[i].pos.y + rect[i].size.y;
			if(!dim1(py_cords, by_cords)){
				return false;
			}
		}
	}

	return true;
}



bool Player::dim1(sf::Vector2f player, sf::Vector2f box)
{
	if(player.x < box.y && box.x<player.y){
		return false;
	}
	return true;
}
