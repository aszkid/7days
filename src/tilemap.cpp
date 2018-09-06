#include "tilemap.h"

void TileMap::draw(sf::RenderTarget& t, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_tset;
	t.draw(m_verts, states);
}

void TileMap::build(sf::Texture set, size_t h, size_t w, sf::Vector2f st, const int* tiles)
{
	m_tset = set;
	m_width = w;
	m_height = h;
	m_stex = st;
}
