#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_chunk.h"

class Map
{
private:
	jgl::Map<jgl::Vector2Int, Chunk*> _chunks;

public:
	Map();

	jgl::Map<jgl::Vector2Int, Chunk*>& chunks() { return (_chunks); }

	void add_chunk(jgl::Vector2Int p_pos, Chunk* p_chunk);
	Chunk* chunk(jgl::Vector2Int p_pos);
};