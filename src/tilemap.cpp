#include "tilemap.h"

void TileMap::draw(sf::RenderTarget &t, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tset;
	t.draw(m_verts, states);
}

void TileMap::build(sf::Texture set, size_t h, size_t w, sf::Vector2f st,
		    const int *tiles)
{
	m_tset = set;
	m_width = w;
	m_height = h;
	m_stex = st;

	m_verts.setPrimitiveType(sf::Quads);
	m_verts.resize(4 * m_width * m_height);

	for (size_t i = 0; i < m_width; i++) {
		for (size_t j = 0; j < m_height; j++) {
			int tileNum = tiles[i + j * m_width];
			int a = m_tset.getSize().x / m_stex.x;
			int tu = tileNum % (a);
			int tv = tileNum / (m_tset.getSize().x / m_stex.x);

			sf::Vertex *quad = &m_verts[(i + j * m_width) * 4];

			quad[0].position =
				sf::Vector2f(i * m_stex.x, j * m_stex.y);
			quad[1].position =
				sf::Vector2f((i + 1) * m_stex.x, j * m_stex.y);
			quad[2].position = sf::Vector2f((i + 1) * m_stex.x,
							(j + 1) * m_stex.y);
			quad[3].position =
				sf::Vector2f(i * m_stex.x, (j + 1) * m_stex.y);

			//Agafa la textura del tile set
			quad[0].texCoords =
				sf::Vector2f(tu * m_stex.x, tv * m_stex.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * m_stex.x,
							 tv * m_stex.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * m_stex.x,
							 (tv + 1) * m_stex.y);
			quad[3].texCoords = sf::Vector2f(tu * m_stex.x,
							 (tv + 1) * m_stex.y);
		}
	}
}
