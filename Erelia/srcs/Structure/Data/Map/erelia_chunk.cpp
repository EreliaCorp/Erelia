#include "erelia.h"

jgl::String Chunk::compose_chunk_file_name(jgl::String p_path, jgl::Vector2Int p_pos)
{
	return (p_path + Path_atlas::chunk_name_file + jgl::itoa(p_pos.x) + "x" + jgl::itoa(p_pos.y) + "y" + Path_atlas::chunk_extension);
}

Chunk::Chunk(jgl::Vector2Int p_pos)
{
	_pos = p_pos;
	for (jgl::Size_t i = 0; i < C_SIZE; i++)
	{
		for (jgl::Size_t j = 0; j < C_SIZE; j++)
		{
			_encounter[i][j] = -1;
			for (jgl::Size_t h = 0; h < C_LAYER_LENGTH; h++)
			{
				_content[i][j][h] = -1;
			}
		}
	}
		
	unbake();
}

void Chunk::save(jgl::String p_folder_path)
{
	jgl::File file = jgl::open_file(compose_chunk_file_name(p_folder_path, _pos), jgl::File_mode::out_binary);

	file.write(reinterpret_cast<char*>(_content), sizeof(_content));
	file.write(reinterpret_cast<char*>(_encounter), sizeof(_encounter));
}

void Chunk::load(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in_binary);

	if (file.eof() == false)
	{
		file.read(reinterpret_cast<char*>(_content), sizeof(_content));
	}
	if (file.eof() == false)
	{
		file.read(reinterpret_cast<char*>(_encounter), sizeof(_encounter));
	}
}

void Chunk::set_encounter(jgl::Vector2Int p_pos, jgl::Int p_value)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE)
		return;
	_encounter[p_pos.x][p_pos.y] = p_value;
}

jgl::Int Chunk::encounter(jgl::Vector2Int p_pos)
{
	if (p_pos.x < 0 || p_pos.x >= C_SIZE ||
		p_pos.y < 0 || p_pos.y >= C_SIZE)
		return (-1);
	return (_encounter[p_pos.x][p_pos.y]);
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
		return (-1);
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

jgl::Vector3Int Chunk::convert_absolute_to_relative_pos(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	return (convert_absolute_to_relative_pos(jgl::Vector3Int(p_pos.x, p_pos.y, p_level)));
}

jgl::Vector3Int Chunk::convert_absolute_to_relative_pos(jgl::Vector3Int p_pos)
{
	jgl::Vector3Int result;

	jgl::Vector2Int chunk_pos = Map::convert_world_to_chunk(p_pos);

	result.x = p_pos.x - chunk_pos.x * Chunk::C_SIZE;
	result.y = p_pos.y - chunk_pos.y * Chunk::C_SIZE;
	result.z = p_pos.z;

	return (result);
}

jgl::Vector3Int Chunk::convert_relative_to_absolute_pos(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	jgl::Vector3Int result;

	result.x = p_chunk_pos.x * Chunk::C_SIZE + p_pos.x;
	result.y = p_chunk_pos.y * Chunk::C_SIZE + p_pos.y;
	result.z = p_level % Chunk::C_LAYER_LENGTH;

	return (result);
}

jgl::Vector3Int Chunk::convert_relative_to_absolute_pos(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos)
{
	jgl::Vector3Int result;

	result.x = p_chunk_pos.x * Chunk::C_SIZE + p_pos.x;
	result.y = p_chunk_pos.y * Chunk::C_SIZE + p_pos.y;
	result.z = p_pos.y % Chunk::C_LAYER_LENGTH;

	return (result);
}

jgl::Vector3Int Chunk::convert_relative_to_absolute_pos(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	return (convert_relative_to_absolute_pos(_pos, p_pos, p_level));
}

jgl::Vector3Int Chunk::convert_relative_to_absolute_pos(jgl::Vector3Int p_pos)
{
	return (convert_relative_to_absolute_pos(_pos, p_pos));
}

jgl::Vector2Int Chunk::convert_absolute_to_relative_pos(jgl::Vector2Int p_pos)
{
	jgl::Vector2Int result;

	jgl::Vector2Int chunk_pos = Map::convert_world_to_chunk(p_pos);

	result.x = p_pos.x - chunk_pos.x * Chunk::C_SIZE;
	result.y = p_pos.y - chunk_pos.y * Chunk::C_SIZE;

	return (result);
}

jgl::Vector2Int Chunk::convert_relative_to_absolute_pos(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos)
{
	jgl::Vector2Int result;

	result.x = p_chunk_pos.x * Chunk::C_SIZE + p_pos.x;
	result.y = p_chunk_pos.y * Chunk::C_SIZE + p_pos.y;

	return (result);
}