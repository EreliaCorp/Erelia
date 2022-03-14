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

	static jgl::Size_t size;

	jgl::String name;
	jgl::Vector2Int sprite;
	jgl::Int animation_size;
	jgl::Bool autotiled;
	jgl::Short obstacle;

	Node(jgl::String p_name, jgl::Vector2Int p_sprite, jgl::Bool p_autotiled, jgl::Short p_obstacle, jgl::Int p_animation_size) :
		name(p_name), sprite(p_sprite), autotiled(p_autotiled), obstacle(p_obstacle), animation_size(p_animation_size)
	{

	}
};

struct Prefab
{
public:
	jgl::String name;
	jgl::Vector2Int sprite;
	jgl::Vector2Int size;
	jgl::Int** levels;
	jgl::Short** composition;

	Prefab(jgl::String p_name, jgl::Vector2Int p_sprite, jgl::Vector2Int p_size, jgl::Array<jgl::Int> p_composition, jgl::Array<jgl::Short> p_level) :
		name(p_name), sprite(p_sprite), size(p_size)
	{
		levels = new jgl::Int * [size.x];
		for (jgl::Int i = 0; i < size.x; i++)
			levels[i] = new jgl::Int[size.y];

		composition = new jgl::Short * [size.x];
		for (jgl::Int i = 0; i < size.x; i++)
			composition[i] = new jgl::Short[size.y];

		if (p_level.size() == 0)
		{
			for (jgl::Int i = 0; i < size.x; i++)
			{
				for (jgl::Int j = 0; j < size.y; j++)
				{
					levels[i][j] = 0;
				}
			}
		}
		else
		{
			for (jgl::Int i = 0; i < size.x; i++)
			{
				for (jgl::Int j = 0; j < size.y; j++)
				{
					levels[i][j] = p_level[i + j * size.x];
				}
			}
		}
		if (p_composition.size() == 0)
		{
			for (jgl::Int i = 0; i < size.x; i++)
			{
				for (jgl::Int j = 0; j < size.y; j++)
				{
					composition[i][j] = 0;
				}
			}
		}
		else
		{
			for (jgl::Int i = 0; i < size.x; i++)
			{
				for (jgl::Int j = 0; j < size.y; j++)
				{
					composition[i][j] = p_composition[i + j * size.x];
				}
			}
		}
	}
};

extern jgl::Array<Node*> g_node_array;
extern jgl::Array<Prefab*> g_prefab_array;