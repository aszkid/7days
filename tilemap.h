#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	bool load(const std::string& tex, const std::vector<uint8_t>* tiles);
	TileMap(sf::Texture m_texture, float width, float height, float t_textures, float t_world);	// Crea TileMap
	virtual void draw(sf::RenderTarget& t, sf::RenderStates states) const;

private:
	sf::Texture m_texture; 		// Texture set
	sf::VertexArray m_verts; 	// Array de tots els vertexs

	float width;			// Textures de llarg del mapa
	float height;		
	float t_textures;		// Nombre pixels textura
	float t_world;			// No se encara que fot ben be
	
	void addTileVertex(Tile tile, sf::Vector2f position);
	
};

