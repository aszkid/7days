#include <SFML/Graphics.hpp>
#include "tilemap.h"

void tilemap::draw(sf::RenderTarget& t, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &tset;

        // drawing tilemap
        t.draw(mverts, states);
}


tilemap::tilemap(void) {}

void tilemap::build(sf::Texture set, unsigned int h, unsigned int w, sf::Vector2f st, const int* tiles)
{
	tset = set;
	width = w;
	height = h;
	stex = st;

	mverts.setPrimitiveType(sf::Quads);
	mverts.resize(4*width*height);
	
	for (unsigned int i = 0 ; i < width; i++)
	{
		for(unsigned int j = 0; j< height; j++)
		{
			
			//Determina la posicio de la tile al tile set
			int tileNumber = tiles[i + j * width];
			int a =  tset.getSize().x / stex.x;			
			int tu = tileNumber % (a);
			int tv = tileNumber / (tset.getSize().x / stex.x);

			sf::Vertex* quad = &mverts[(i+j*width)*4];
			
			//Determina la posicio de la tile al mon
			quad[0].position = sf::Vector2f(i*stex.x, j*stex.y);
			quad[1].position = sf::Vector2f((i+1)*stex.x, j * stex.y);
			quad[2].position = sf::Vector2f((i+1)*stex.x, (j+1) * stex.y);
			quad[3].position = sf::Vector2f(i*stex.x, (j+1)*stex.y);
			
			//Agafa la textura del tile set
			quad[0].texCoords = sf::Vector2f(tu * stex.x, tv * stex.y);
			quad[1].texCoords = sf::Vector2f((tu+1) * stex.x, tv * stex.y);
			quad[2].texCoords = sf::Vector2f((tu+1) * stex.x, (tv+1) * stex.y);
			quad[3].texCoords = sf::Vector2f(tu * stex.x , (tv+1) * stex.y);

		}
	}
}

