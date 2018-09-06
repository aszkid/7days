#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	void build(sf::Texture set, size_t h, size_t w, sf::Vector2f st, const int* tiles);
	virtual void draw(sf::RenderTarget& t, sf::RenderStates states) const;

private:
	sf::Texture m_tset; // Texture set
	sf::VertexArray m_verts; // Array de tots els vertexs

	size_t m_width; // Textures de llarg del mapa
	size_t m_height;
	sf::Vector2f m_stex;
};

