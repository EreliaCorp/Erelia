#include "erelia.h"


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

void Map::send_area_edition_command(jgl::Vector2Int p_pos_start, jgl::Vector2Int p_pos_end, jgl::Int value)
{
	static Message msg(Server_message::Encounter_modification);

	msg.clear();

	for (jgl::Int x = p_pos_start.x; x <= p_pos_end.x; x++)
	{
		for (jgl::Int y = p_pos_start.y; y <= p_pos_end.y; y++)
		{
			jgl::Vector2Int tmp_pos = jgl::Vector2Int(x, y);
			if (Engine::instance()->map()->encounter(tmp_pos) != value)
			{
				Engine::instance()->map()->place_encounter(tmp_pos, value);
				msg << tmp_pos << value;
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

jgl::Int Map::encounter(jgl::Vector2Int p_pos)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk == nullptr)
		return (-2);

	jgl::Vector2Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

	return (tmp_chunk->encounter(rel_pos));
}

void Map::place_encounter(jgl::Vector2Int p_pos, jgl::Int p_value)
{
	jgl::Vector2Int chunk_pos = convert_world_to_chunk(p_pos);

	Chunk* tmp_chunk = chunk(chunk_pos);

	if (tmp_chunk != nullptr)
	{
		jgl::Vector2Int rel_pos = tmp_chunk->convert_absolute_to_relative_pos(p_pos);

		jgl::Short value = tmp_chunk->encounter(rel_pos);

		if (value != p_value)
		{
			tmp_chunk->set_encounter(rel_pos, p_value);
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

jgl::Bool Map::can_move(Entity* p_entity, jgl::Vector2 p_start, jgl::Vector2 p_direction)
{
	if (p_entity->is_flying() == true)
		return (true);

	jgl::Vector2 p_destination = p_start + p_direction;
	static jgl::Vector2Int direction_value[8] = {
		jgl::Vector2Int(-1, -1),
		jgl::Vector2Int(0, -1),
		jgl::Vector2Int(1, -1),
		jgl::Vector2Int(1, 0),
		jgl::Vector2Int(-1, 0),
		jgl::Vector2Int(-1, 1),
		jgl::Vector2Int(0, 1),
		jgl::Vector2Int(1, 1),
	};
	static jgl::Int direction_mask[8] = {
		Node::NORTH_WALKABLE | Node::WEST_WALKABLE,
		Node::NORTH_WALKABLE,
		Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
		Node::EAST_WALKABLE,
		Node::WEST_WALKABLE,
		Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
		Node::SOUTH_WALKABLE,
		Node::SOUTH_WALKABLE | Node::EAST_WALKABLE
	};
	static jgl::Int rev_direction_mask[8] = {
		Node::SOUTH_WALKABLE | Node::EAST_WALKABLE,
		Node::SOUTH_WALKABLE,
		Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
		Node::WEST_WALKABLE,
		Node::EAST_WALKABLE,
		Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
		Node::NORTH_WALKABLE,
		Node::NORTH_WALKABLE | Node::WEST_WALKABLE
	};

	jgl::Size_t index = 0;
	for (index = 0; index < 8 && direction_value[index] != p_direction; index++){}

	jgl::Short value = Node::WALKABLE;
	jgl::Short destination_value = Node::WALKABLE;
	for (jgl::Size_t i = 0; i < Chunk::C_LAYER_LENGTH; i++)
	{
		jgl::Short pos_value = content(p_start, i);
		jgl::Short destination_pos_value = content(p_destination, i);

		if (i == 0 && pos_value == -1)
			value = Node::OBSTACLE;
		if (i == 0 && destination_pos_value == -1)
			destination_value = Node::OBSTACLE;
		if (pos_value != -1)
			value &= g_node_array[pos_value]->obstacle;
		if (destination_pos_value != -1)
			destination_value &= g_node_array[destination_pos_value]->obstacle;
	}

	if ((value & direction_mask[index]) != direction_mask[index] || (destination_value & rev_direction_mask[index]) != rev_direction_mask[index])
		return (false);
	return (true);
}