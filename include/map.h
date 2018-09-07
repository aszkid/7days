#pragma once

#include <vector>
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <jdm/path.h>

struct CollisionRect {
	sf::Vector2f size;
	sf::Vector2f pos;
};

struct TileLayer {
	std::vector<uint32_t> data;
	std::string name;

	enum Type { GROUND, OBJECT };
	Type type;
};

struct Map {
	size_t width, height;
	size_t tile_size;

	std::vector<TileLayer> tile_layers;
	std::vector<CollisionRect> collision_rects;

	sf::Texture tile_set;

	/*
	 * API
	 */
	static bool from_json(Map *map, const jdm::path &file);
	static void build_verts(const Map *map,
				std::vector<sf::VertexArray> *varrs);
	static void build_bboxes(const Map *map,
				sf::VertexArray *varr);
};
