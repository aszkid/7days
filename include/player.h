#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <jdm/path.h>

struct Player {
	sf::Vector2f p_position;
	sf::Texture p_texture;
	
	float p_width;
	float p_height;

	static bool from_json(Player *player,  const jdm::path &file);
};
