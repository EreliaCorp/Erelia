#pragma once
#include "jgl.h"
#include "structure/Data/Engine/erelia_engine.h"

namespace Map_generator
{
	void generate_node_tiles(jgl::String p_path);
	void generate_wall_tiles(jgl::String p_path);
	void generate_biome_scenery(jgl::String p_path);
}