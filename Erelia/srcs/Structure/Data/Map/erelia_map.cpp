#include "erelia.h"


Map::Map()
{

}

void Map::add_chunk(jgl::Vector2Int p_pos, Chunk* p_chunk)
{
	_chunks[p_pos] = p_chunk;
}

Chunk* Map::chunk(jgl::Vector2Int p_pos)
{
	if (_chunks.count(p_pos) == 0)
		return (nullptr);
	return (_chunks[p_pos]);
}