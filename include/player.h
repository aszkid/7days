#pragma once

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <jdm/path.h>

struct CollisionRect {
        sf::Vector2f size;
        sf::Vector2f pos;
};


struct Player {
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Texture texture;

	static bool from_json(Player *player,  const jdm::path &file);
	bool can_move(Player player, std::vector<CollisionRect> collision_rect);
	bool dim1(sf::Vector2f p, sf::Vector2f b);
};
