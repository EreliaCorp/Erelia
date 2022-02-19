#include "erelia.h"

Chunk::Chunk(jgl::Vector2Int p_pos)
{
	_pos = p_pos;
	for (jgl::Size_t i = 0; i < C_SIZE; i++)
		for (jgl::Size_t j = 0; j < C_SIZE; j++)
			for (jgl::Size_t h = 0; h < C_SIZE; h++)
			{
				_content[i][j][h] = -1;
			}
}

void Chunk::set_content(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_value)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE ||
		p_level < 0 || p_level >= C_LAYER_LENGTH)
		return;
	_content[p_pos.x][p_pos.y][p_level] = p_value;
}

void Chunk::set_content(jgl::Vector3Int p_pos, jgl::Short p_value)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE ||
		p_pos.z < 0 || p_pos.z >= C_LAYER_LENGTH)
		return;
	_content[p_pos.x][p_pos.y][p_pos.z] = p_value;
}

jgl::Short Chunk::content(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE ||
		p_level < 0 || p_level >= C_LAYER_LENGTH)
		return (- 1);
	return (_content[p_pos.x][p_pos.y][p_level]);
}

jgl::Short Chunk::content(jgl::Vector3Int p_pos)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE ||
		p_pos.z < 0 || p_pos.z >= C_LAYER_LENGTH)
		return (-1);
	return (_content[p_pos.x][p_pos.y][p_pos.z]);
}

Node* Chunk::node(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	jgl::Short value = content(p_pos, p_level);

	if (value < 0 || static_cast<jgl::Size_t>(value) > g_node_array.size())
		return (nullptr);
	return (g_node_array[value]);
}

Node* Chunk::node(jgl::Vector3Int p_pos)
{
	jgl::Short value = content(p_pos);

	if (value < 0 || static_cast<jgl::Size_t>(value) > g_node_array.size())
		return (nullptr);
	return (g_node_array[value]);
}
