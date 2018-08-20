#include "tilemap.h"

bool TileMap::load(const std::string& tex, const std::vector<uint8_t>* tiles)
{
	if (!m_texture.loadFromFile(tex))
		return false;

	m_verts.setPrimitiveType(sf::Quads);
}


void TileMap::draw(sf::RenderTarget& t, sf::RenderStates states) const
{
	// drawing tilemap
	states.transform *= getTransform();
	states.texture = &m_texture;
	t.draw(m_verts, states);
}
