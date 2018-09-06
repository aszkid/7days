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

void Map::build_verts(const Map *map, std::vector<sf::VertexArray>* varrs)
{
	const size_t tex_w = map->tile_set.getSize().x;

	for (const auto& l : map->tile_layers) {
		varrs->emplace_back(sf::Quads, 4 * map->width * map->height);
		auto& varr = varrs->back();

		for (size_t i = 0; i < map->width; i++) {
			for (size_t j = 0; j < map->height; j++) {
				/*
				 * Vertex coords
				 */
				sf::Vertex *quad = &varr[(i + j * map->width) * 4];

				quad[0].position =
					sf::Vector2f(i * map->tile_size, j * map->tile_size);
				quad[1].position =
					sf::Vector2f((i + 1) * map->tile_size, j * map->tile_size);
				quad[2].position = sf::Vector2f((i + 1) * map->tile_size,
								(j + 1) * map->tile_size);
				quad[3].position =
					sf::Vector2f(i * map->tile_size, (j + 1) * map->tile_size);
				
				/*
				 * Fetch texture coords
				 */
				size_t n_tile = l.data[i + j * map->width];
				if (n_tile == 0) {
					// Empty tile -- use (0,0) texture, should be empty!
					// 
					quad[0].texCoords = sf::Vector2f(0, 0);
					quad[1].texCoords = sf::Vector2f(map->tile_size, 0);
					quad[2].texCoords = sf::Vector2f(map->tile_size, map->tile_size);
					quad[3].texCoords = sf::Vector2f(0, map->tile_size);
					continue;
				}

				// Fix indexing offset
				//
				n_tile -= 1;

				int a = tex_w / map->tile_size;
				int tu = n_tile % (a);
				int tv = n_tile / (tex_w / map->tile_size);

				//Agafa la textura del tile set
				quad[0].texCoords =
					sf::Vector2f(tu * map->tile_size, tv * map->tile_size);
				quad[1].texCoords = sf::Vector2f((tu + 1) * map->tile_size,
								 tv * map->tile_size);
				quad[2].texCoords = sf::Vector2f((tu + 1) * map->tile_size,
								 (tv + 1) * map->tile_size);
				quad[3].texCoords = sf::Vector2f(tu * map->tile_size,
								 (tv + 1) * map->tile_size);
			}
		}
	}
}
