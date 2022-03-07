#pragma once

#include "jgl.h"

enum class Item_type
{
	Error = -1,
	Node = 0,
	Prefab = 1
};

struct Item
{
	Item_type type;

	Item(Item_type p_type = Item_type::Error)
	{
		type = p_type;
	}
};

struct Node_item : public Item
{
	jgl::Short value;

	Node_item(jgl::Short p_value);
	void use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end);
};

struct Prefab_item : public Item
{
	jgl::Short value;

	Prefab_item(jgl::Short p_value);
	void use(jgl::Vector3Int p_pos);
};