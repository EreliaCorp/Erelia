#pragma once

#include "jgl.h"

struct Node
{
	static const jgl::Short OBSTACLE			= 0b0000000000000000;
	static const jgl::Short NORTH_WALKABLE		= 0b0000000000000001;
	static const jgl::Short EAST_WALKABLE		= 0b0000000000000010;
	static const jgl::Short SOUTH_WALKABLE		= 0b0000000000000100;
	static const jgl::Short WEST_WALKABLE		= 0b0000000000001000;
	static const jgl::Short WALKABLE			= 0b0000000000001111;

	static const jgl::Size_t SIZE = 32;

	jgl::Short obstacle;
	jgl::Bool autotiled;
	jgl::Vector2Int sprite;
	jgl::Size_t animation_size;

	Node(jgl::Short p_obstacle = Node::WALKABLE, jgl::Bool p_autotiled = false, jgl::Vector2Int p_sprite = 0, jgl::Size_t p_animation_size = 1u)
	{
		obstacle = p_obstacle;
		autotiled = p_autotiled;
		sprite = p_sprite;
		animation_size = p_animation_size;
	}
};

extern jgl::Array<Node*> g_node_array;