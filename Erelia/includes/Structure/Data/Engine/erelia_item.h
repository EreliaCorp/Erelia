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
	void fill(jgl::Vector3Int p_pos);
	void use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end);
	void paint(jgl::Vector3Int p_pos, jgl::Size_t p_radius);
	void paint_wall(jgl::Vector3Int p_pos);
};

struct Prefab_item : public Item
{
private:
	void _use(jgl::Vector3Int p_pos);
	void _remove(jgl::Vector3Int p_pos);

public:
	jgl::Short value;

	Prefab_item(jgl::Short p_value);
	void use(jgl::Vector3Int p_pos);
	void use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end);
	void remove(jgl::Vector3Int p_pos);
	void remove(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end);
};