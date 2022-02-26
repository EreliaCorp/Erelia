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