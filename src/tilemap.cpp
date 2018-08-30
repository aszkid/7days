#include "tilemap.h"
#include "tile.h"

bool TileMap::load(const std::string& tex, const std::vector<uint8_t>* tiles, float width, float height)
{
	if (!m_texture.loadFromFile(tex))
		return false;

	m_verts.setPrimitiveType(sf::Quads);

	m_verts = new VertexArray(sf::PrimitiveType Quads, )
}


void TileMap::draw(sf::RenderTarget& t, sf::RenderStates states) const
{
	// drawing tilemap
	states.Texture = m_texture;
	t.draw(m_verts, states)
}

TileMap::TileMap(sf::Texture m_texture, float width, float height, float t_textures, float t_world)
{
	m_texture = m_texture;
	Tilemap.width = width;
	Tilemap.height = height;
	Tilemap.t_textures = t_textures;
	Tilemap.t_world = t_world;

	m_verts = new sf::VertexArray(sf::PrimitiveType sf::Quads, (uint) (4*width*height)); // width*height = nombre total de tiles
	
	tile = new sf::Vector2f(0,1);
	for(int x = 0; x < width; x++)
	{
		for(int y = 0, y< height; y++)
		{
			addTileVertex(tile, new sf::Vector2f((float) x, (float) y));
		}
	}
}

TileMap::addTileVertex(Tile tile, sf::Vector2f position);
{
	m_verts.Append(	new sf::Vertex(new (sf::Vector2f(0.0f, 0.0f) + position)*t_world), 
			new sf:Vector2f(t_textures*tile.X, t_textures*tile.y));

	m_verts.Append( new sf::Vertex(new (sf::Vector2f(1.0f, 0.0f) + position)*t_world),
                        new sf:Vector2f((t_textures*tile.X) + t_textures, t_textures*tile.y));

	m_verts.Append( new sf::Vertex(new (sf::Vector2f(1.0f, 1.0f) + position)*t_world),
                        new sf:Vector2f((t_textures*tile.X) + t_textures, (t_textures*tile.y) + t_textures));

	m_verts.Append( new sf::Vertex(new (sf::Vector2f(0.0f, 1.0f) + position)*t_world),
                        new sf:Vector2f(t_textures*tile.X, (t_textures*tile.y) + t_textures));
}

