#pragma once

#include "jgl.h"

#include <set>
#include "Structure/Data/Map/erelia_chunk.h"

class Map
{
private:

	struct AStar_node
	{
		jgl::Float distance;
		jgl::Vector2Int pos;
		jgl::Vector2Int delta;
		const AStar_node* parent;
		jgl::Size_t path_len;

		AStar_node()
		{
			distance = -1;
			pos = 0;
			delta = 0;
			parent = nullptr;
			path_len = 0;
		}
		AStar_node(jgl::Float p_distance, jgl::Vector2Int p_pos, jgl::Vector2Int p_delta, const AStar_node* p_parent, jgl::Size_t p_path_len)
		{
			distance = p_distance;
			pos = p_pos;
			delta = p_delta;
			parent = p_parent;
			path_len = p_path_len;
		}

		bool operator<(const AStar_node& other) const
		{
			return distance < other.distance;
		}

		friend std::ostream& operator<<(std::ostream& os, const AStar_node& value)
		{
			os << value.pos;
			return os;
		}
	};

	jgl::Map<jgl::Vector2Int, Chunk*> _chunks;

	void _generate_chunk(Chunk* p_chunk);
	void _calc_result(const Map::AStar_node* destination, jgl::Array<jgl::Vector2Int>& p_path);
	const AStar_node* _found_closest_node(jgl::Array<AStar_node>& p_to_calc, jgl::Size_t p_first_index);

public:

	Map();

	jgl::Map<jgl::Vector2Int, Chunk*>& chunks() { return (_chunks); }

	void save();
	void load();

	void set_node_size(jgl::Size_t p_node_size) { Node::size = p_node_size; unbake(); }

	jgl::Short content(jgl::Vector2Int p_pos, jgl::Size_t p_level);
	jgl::Short content(jgl::Vector3Int p_pos);

	jgl::Int teleporter(jgl::Vector2Int p_pos);

	void place_node(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_node);
	void place_node(jgl::Vector3Int p_pos, jgl::Short p_node);

	void place_teleporter(jgl::Vector2Int p_pos, jgl::Int p_value);

	void add_chunk(Chunk* p_chunk);

	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector2Int p_pos);
	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector3Int p_pos);
	static jgl::Vector2Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos = 0);
	static jgl::Vector3Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos = 0);

	Chunk* request_chunk(jgl::Vector2Int p_chunk_pos);
	Chunk* chunk(jgl::Vector2Int p_pos);

	void unbake();

	jgl::Bool can_acces(jgl::Vector2Int p_start, jgl::Vector2Int p_direction);
	void find_path(jgl::Array<jgl::Vector2Int>& p_path, jgl::Vector2Int p_source, jgl::Vector2Int p_destination, jgl::Int p_max_length = 50);
	jgl::Array<jgl::Vector2Int> find_path(jgl::Vector2Int p_source, jgl::Vector2Int p_destination, jgl::Int p_max_length = 50);
};