#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_chunk.h"

class Map
{
private:
	struct Generation_data
	{
		jgl::Ulong _seed;
		jgl::Perlin* _ground_perlin_alpha;
		jgl::Perlin* _ground_perlin_beta;

		Generation_data(jgl::Ulong p_seed) :
			_seed(p_seed), _ground_perlin_alpha(nullptr), _ground_perlin_beta(nullptr)
		{
			_seed = p_seed;
			_ground_perlin_alpha = new jgl::Perlin(_seed);
			_ground_perlin_beta = new jgl::Perlin((_seed ^ 14568746548) * 11);
		}

		void reseed(jgl::Ulong p_seed)
		{
			_seed = p_seed;
			_ground_perlin_alpha->reseed(_seed);
			_ground_perlin_beta->reseed(_seed);
		}
	};

	jgl::Map<jgl::Vector2Int, Chunk*> _chunks;

	jgl::String _world_path;
	Generation_data* _generation_data;

	void _generate_chunk(Chunk* p_chunk);

public:

	Map();

	jgl::Map<jgl::Vector2Int, Chunk*>& chunks() { return (_chunks); }

	void save();
	void load(jgl::String p_world_path);

	void set_node_size(jgl::Size_t p_node_size) { Node::size = p_node_size; unbake(); }

	void place_node(jgl::Vector2Int p_pos, jgl::Size_t p_level, jgl::Short p_node);
	void place_node(jgl::Vector3Int p_pos, jgl::Short p_node);

	void add_chunk(jgl::Vector2Int p_pos, Chunk* p_chunk);

	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector2Int p_pos);
	static jgl::Vector2Int convert_world_to_chunk(jgl::Vector3Int p_pos);
	static jgl::Vector2Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector2Int p_pos = 0);
	static jgl::Vector3Int convert_chunk_to_world(jgl::Vector2Int p_chunk_pos, jgl::Vector3Int p_pos = 0);

	Chunk* request_chunk(jgl::Vector2Int p_chunk_pos);
	Chunk* chunk(jgl::Vector2Int p_pos);

	void unbake();
};