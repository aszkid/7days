#pragma once

#include <vector>
#include <cstdint>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

enum LayerType {
	GROUND, OBJECTS
};

struct CollisionRect {
	sf::Vector2f size;
	sf::Vector2f pos;
};

struct TileLayer {
	std::vector<size_t> tiles;
	std::string name;
	LayerType type;
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
	static bool from_json(Map* map, const std::string prefix, const std::string file);
};

