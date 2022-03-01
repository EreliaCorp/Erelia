#include "erelia.h"


Map::Map()
{
	_world_path = "";
	_generation_data = new Map::Generation_data(0);
}

void Map::save()
{
	for (auto tmp : _chunks)
	{
		tmp.second->save(_world_path + "/chunk/");
	}
}

void Map::load(jgl::String p_world_path)
{
	_world_path = p_world_path;
	jgl::Ulong new_seed = 7846581234;
	_generation_data->reseed(new_seed);
}

void Map::unbake()
{
	for (auto tmp : _chunks)
	{
		tmp.second->unbake();
	}
}

void Map::_generate_chunk(Chunk* p_chunk)
{
	for (jgl::Size_t i = 0; i < Chunk::C_SIZE; i++)
		for (jgl::Size_t j = 0; j < Chunk::C_SIZE; j++)
		{
			if (p_chunk->pos() == 0 && (i == 0 || j == 0))
			{
				p_chunk->set_content(jgl::Vector3Int(i, j, 0), 0);
			}
			else
				p_chunk->set_content(jgl::Vector3Int(i, j, 0), 14);
		}
}

Chunk* Map::request_chunk(jgl::Vector2Int p_chunk_pos)
{
	Chunk* result = new Chunk(p_chunk_pos);

	jgl::String chunk_file_path = Chunk::compose_chunk_file_name(_world_path + "/chunk/", p_chunk_pos);

	if (jgl::check_file_exist(chunk_file_path) == true)
	{
		result->load(chunk_file_path);
	}
	else
	{
		_generate_chunk(result);
	}

	add_chunk(p_chunk_pos, result);

	return (result);
}

void Map::place_node(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_node)
{
	place_node(jgl::Vector3Int(p_pos.x, p_pos.y, p_level), p_node);
}

void Map::place_node(jgl::Vector3Int p_pos, jgl::Short p_node)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk != nullptr)
	{
		jgl::Vector3Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

		jgl::Short value = tmp_chunk->content(rel_pos);

		if (value != p_node)
		{
			tmp_chunk->set_content(rel_pos, p_node);
			tmp_chunk->unbake();
		}
	}
}

jgl::Vector2Int Map::convert_world_to_chunk(jgl::Vector2Int p_pos)
{
	jgl::Vector2 result;

	result.x = static_cast<jgl::Float>(p_pos.x) / static_cast<jgl::Float>(Chunk::C_SIZE);
	result.y = static_cast<jgl::Float>(p_pos.y) / static_cast<jgl::Float>(Chunk::C_SIZE);

	result = result.floor();

	return (result);
}

jgl::Vector2Int Map::convert_world_to_chunk(jgl::Vector3Int p_pos)
{
	return (convert_world_to_chunk(jgl::Vector2Int(p_pos.x, p_pos.y)));
}

jgl::Vector2Int Map::convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos)
{
	return (p_chunk_pos * Chunk::C_SIZE + p_pos);
}

jgl::Vector3Int Map::convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos)
{
	jgl::Vector3Int converted = jgl::Vector3Int(p_chunk_pos.x, p_chunk_pos.y, 0) * Chunk::C_SIZE;
	return (converted + p_pos);
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