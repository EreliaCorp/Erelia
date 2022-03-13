#include "erelia.h"


Map::Map()
{
	_world_path = "";
}

void Map::save()
{
	for (auto tmp : _chunks)
	{
		tmp.second->save(_world_path + Path_atlas::chunk_sub_path);
	}
}

void Map::load(jgl::String p_world_path)
{
	_world_path = p_world_path;
	unbake();
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
	Chunk* result = chunk(p_chunk_pos);

	if (result == nullptr)
	{
		result = new Chunk(p_chunk_pos);

		jgl::String chunk_file_path = Chunk::compose_chunk_file_name(_world_path + "/chunk/", p_chunk_pos);

		if (jgl::check_file_exist(chunk_file_path) == true)
		{
			result->load(chunk_file_path);
		}
		else
		{
			_generate_chunk(result);
		}

		add_chunk(result);
	}

	return (result);
}

jgl::Short Map::content(jgl::Vector2Int p_pos, jgl::Size_t p_level)
{
	return (content(jgl::Vector3Int(p_pos.x, p_pos.y, p_level)));
}

void Map::send_edition_command(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end, jgl::Short value)
{
	static Message msg(Server_message::Chunk_modification);

	msg.clear();

	for (jgl::Int x = p_pos_start.x; x <= p_pos_end.x; x++)
	{
		for (jgl::Int y = p_pos_start.y; y <= p_pos_end.y; y++)
		{
			for (jgl::Int z = p_pos_start.z; z <= p_pos_end.z; z++)
			{
				jgl::Vector3Int tmp_pos = jgl::Vector3Int(x, y, z);
				if (Engine::instance()->map()->content(tmp_pos) != value)
				{
					Engine::instance()->map()->place_node(tmp_pos, value);
					msg << tmp_pos << value;
				}
			}
		}
	}

	if (msg.empty() == false)
		Client_manager::client()->send(msg);
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