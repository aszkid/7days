#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tex, const std::vector<uint8_t>* tiles);
private:
	virtual void draw(sf::RenderTarget& t, sf::RenderStates states) const;

	sf::Texture m_texture;
	sf::VertexArray m_verts;
};

