#include "map.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <spdlog/spdlog.h>

using nlohmann::json;



bool Map::from_json(Map* m, const std::string prefix, const std::string file)
{
	auto log = spdlog::get("console");

	std::ifstream infile(prefix + file);
	if (!infile) {
		log->error("Failed to open map `{}`!", file);
		return false;
	}

	json j;
	infile >> j;

	/*
	 * General map info
	 */
	m->width = j["width"];
	m->height = j["height"];
	m->tile_size = j["tilewidth"];

	if (m->tile_size != j["tileheight"]) {
		log->error("Tiles have to be squares!");
		return false;
	}


	/*
	 * Tile set
	 */
	json tset = j["tilesets"][0];
	if (tset.is_null()) {
		log->error("No default tileset!");
		return false;
	}

	const std::string tset_image = tset["image"];
	if (!m->tile_set.loadFromFile(prefix + tset_image)) {
		log->error("Failed at loading tileset texture!");
		return false;
	}



	return true;
}
