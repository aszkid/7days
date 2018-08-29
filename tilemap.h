#pragma once

#include <SFML/Graphics.hpp>

class tilemap: public sf::Drawable, public sf::Transformable
{
public:
	void build(sf::Texture, unsigned int, unsigned int, sf::Vector2f, const int* tiles);
	tilemap();	
private:
	sf::Texture tset;	//Conjunt de textures
	sf::VertexArray mverts;
	
	unsigned int width;
	unsigned int height;
	sf::Vector2f stex;	//Tamany textures

	virtual void draw(sf::RenderTarget& t, sf::RenderStates states) const;

};
