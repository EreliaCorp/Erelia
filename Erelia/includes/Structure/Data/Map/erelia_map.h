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

	void add_chunk(jgl::Vector2Int p_pos, Chunk* p_chunk);

	Chunk* request_chunk(jgl::Vector2Int p_chunk_pos);
	Chunk* chunk(jgl::Vector2Int p_pos);

	void unbake();
};