#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_node.h"

class Chunk
{
public:
	static const jgl::Size_t C_SIZE = 16;
	static const jgl::Size_t C_LAYER_LENGTH = 5;

private:
	jgl::Vector2Int _pos;
	jgl::Short _content[C_SIZE][C_SIZE][C_LAYER_LENGTH];

	jgl::Bool _baked;

public:
	Chunk(jgl::Vector2Int p_pos = 0);

	jgl::Bool baked() { return (_baked); }
	void bake();

	jgl::Vector2Int pos() { return (_pos); }

	void set_content(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_value);
	void set_content(jgl::Vector3Int p_pos, jgl::Short p_value);

	jgl::Short content(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	jgl::Short content(jgl::Vector3Int p_pos);

	Node* node(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	Node* node(jgl::Vector3Int p_pos);
};