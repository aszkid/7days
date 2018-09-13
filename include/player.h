#pragma once

#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
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
	sf::Sprite sprite;

	static bool from_json(Player *player,  const jdm::path &file);
	
	void build_player(Player *player);

	void move(Player *player, float x, float y, std::vector<CollisionRect> rect);

	bool can_move(Player player, std::vector<CollisionRect> collision_rect);
	bool dim1(sf::Vector2f p, sf::Vector2f b);
};
