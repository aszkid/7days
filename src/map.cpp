#include "map.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <spdlog/spdlog.h>

using nlohmann::json;

bool load_layer(Map *m, const json &j)
{
	auto log = spdlog::get("console");

	const std::string name = j["name"];
	log->info("Parsing layer {}", name);

	if (j["type"] == "tilelayer") {
		TileLayer layer;
		const auto& props = j["properties"];

		if (props.count("object") == 1 &&
		    props["object"] == true) {
			layer.type = TileLayer::Type::OBJECT;

		} else if (props.count("ground") == 1 &&
		           props["ground"] == true) {
			layer.type = TileLayer::Type::GROUND;
		} else {
			log->warn("Unknown tile layer");
		}

		/*
		 * Load data
		 */
		log->info("Loading layer data...");

		layer.name = j["name"];
		size_t w = j["width"];
		size_t h = j["height"];

		layer.data.reserve(w * h);
		std::vector<uint32_t> data = j["data"];
		layer.data = std::move(data);

		/*
		 * Push layer
		 */
		m->tile_layers.push_back(layer);

	} else if (j["type"] == "objectgroup") {
		/*
		 * Dealing with object layer
		 */
		m->collision_rects.reserve(j["objects"].size());
		for (const auto &obj : j["objects"]) {
			sf::Vector2f pos, sz;
			sz.x = obj["width"];
			sz.y = obj["height"];
			pos.x = obj["x"];
			pos.y = obj["y"];
			m->collision_rects.push_back({ sz, pos });
		}

	} else {
		log->warn("Unknown layer");
	}

	return true;
}

bool Map::from_json(Map *m, const std::string prefix, const std::string file)
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

	/*
	 * Map layers
	 */
	for (const auto &layer : j["layers"]) {
		log->info("Extracting layer...");

		if (!load_layer(m, layer)) {
			log->error("Failed to load layer");
			return false;
		}
	}

	return true;
}
