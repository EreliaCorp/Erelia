#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_entity.h"
#include "Structure/Atlas/erelia_path_atlas.h"

Map::Map()
{

}

void Map::save()
{
	for (auto tmp : _chunks)
	{
		tmp.second->save(Path_atlas::world_path + Path_atlas::chunk_sub_path);
	}
}

void Map::load()
{
	unbake();
}

void Map::unbake()
{
	Chunk::set_screen_node_size(0);
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
	Chunk* result = chunk(p_chunk_pos);

	if (result == nullptr)
	{
		result = new Chunk(p_chunk_pos);

		jgl::String chunk_file_path = Chunk::compose_chunk_file_name(Path_atlas::world_path + Path_atlas::chunk_sub_path, p_chunk_pos);

		if (jgl::check_file_exist(chunk_file_path) == true)
		{
			result->load(chunk_file_path);
		}
		else
		{
			_generate_chunk(result);
		}

		//add_chunk(result);
	}

	return (result);
}

jgl::Short Map::content(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	return (content(jgl::Vector3Int(p_pos.x, p_pos.y, p_level)));
}

jgl::Short Map::content(jgl::Vector3Int p_pos)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk == nullptr)
		return (-2);
	
	jgl::Vector3Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

	return (tmp_chunk->content(rel_pos));
}

jgl::Int Map::teleporter(jgl::Vector2Int p_pos)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk == nullptr)
		return (-2);

	jgl::Vector2Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

	return (tmp_chunk->teleporter(rel_pos));
}

void Map::place_teleporter(jgl::Vector2Int p_pos, jgl::Int p_value)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk != nullptr)
	{
		jgl::Vector2Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

		jgl::Short value = tmp_chunk->teleporter(rel_pos);

		if (value != p_value)
		{
			tmp_chunk->set_teleporter(rel_pos, p_value);
			tmp_chunk->unbake();
		}
	}
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

void Map::add_chunk(Chunk* p_chunk)
{
	if (_chunks.count(p_chunk->pos()) != 0)
		delete _chunks[p_chunk->pos()];
	_chunks[p_chunk->pos()] = p_chunk;
}

Chunk* Map::chunk(jgl::Vector2Int p_pos)
{
	if (_chunks.count(p_pos) == 0)
		return (nullptr);
	return (_chunks[p_pos]);
}