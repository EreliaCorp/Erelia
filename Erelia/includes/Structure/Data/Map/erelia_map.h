#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_chunk.h"

class Map
{
private:
	jgl::Map<jgl::Vector2Int, Chunk*> _chunks;

	jgl::String _world_path;

	void _generate_chunk(Chunk* p_chunk);

public:

	Map();

	jgl::Map<jgl::Vector2Int, Chunk*>& chunks() { return (_chunks); }

	void save();
	void load(jgl::String p_world_path);

	void set_node_size(jgl::Size_t p_node_size) { Node::size = p_node_size; unbake(); }

	jgl::Short content(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	jgl::Short content(jgl::Vector3Int p_pos);

	jgl::Int encounter(jgl::Vector2Int p_pos);

	void place_node(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_node);
	void place_node(jgl::Vector3Int p_pos, jgl::Short p_node);

	void place_encounter(jgl::Vector2Int p_pos, jgl::Int p_value);

	void add_chunk(Chunk* p_chunk);

	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector2Int p_pos);
	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector3Int p_pos);
	static jgl::Vector2Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos = 0);
	static jgl::Vector3Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos = 0);

	Chunk* request_chunk(jgl::Vector2Int p_chunk_pos);
	Chunk* chunk(jgl::Vector2Int p_pos);

	void unbake();

	static void send_edition_command(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end, jgl::Short value);
	static void send_area_edition_command(jgl::Vector2Int p_pos_start, jgl::Vector2Int p_pos_end, jgl::Int value);

	jgl::Bool can_move(class Entity* p_entity, jgl::Vector2 p_start, jgl::Vector2 p_direction);
};