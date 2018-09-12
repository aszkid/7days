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

	p -> p_width = j["width"];
	p -> p_height = j["height"];
	p -> p_position.x = j["x"];
	p -> p_position.y = j["y"];
	
	const std::string player_texture = j["image"];
	if(!p -> p_texture.loadFromFile(file / ("../" + player_texture))) {
		//No se com funciona lo dels paths encara
		log -> error("Failed at loading player texture!");
	}
	
	return true;
}
