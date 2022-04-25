#include "Structure/Data/Engine/erelia_item.h"
#include "Structure/Data/Engine/erelia_engine.h"
#include "structure/Data/Map/erelia_chunk.h"
#include "structure/Data/Map/erelia_node.h"
#include "widget/screen/game_world/Widget/erelia_map_operation.h"
#include "widget/screen/game_world/erelia_game_world_screen.h"
#include "network/erelia_client_manager.h"

Message Prefab_item::_prefab_message(Server_message::Chunk_modification);

Node_item::Node_item(jgl::Short p_value) : Item(Item_type::Node)
{
	value = p_value;
}

void Node_item::use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Map_operation::place_multiple_node(p_pos_start, p_pos_end, value);
}

void Node_item::fill(jgl::Vector3Int p_pos)
{
	Map_operation::paint_node(p_pos, value);
}

void Node_item::paint(jgl::Vector3Int p_pos, jgl::Size_t p_radius)
{
	Map_operation::place_circle_node(p_pos, p_radius, value);
}

void Node_item::paint_wall(jgl::Vector3Int p_pos)
{
	Map_operation::paint_wall_node(p_pos, value);
}

Prefab_item::Prefab_item(jgl::Short p_value) : Item(Item_type::Prefab)
{
	value = p_value;
}

void Prefab_item::_use(jgl::Vector3Int p_pos)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	for (jgl::Int delta_x = 0; delta_x < tmp_prefab->size.x; delta_x++)
	{
		for (jgl::Int delta_y = 0; delta_y < tmp_prefab->size.y; delta_y++)
		{
			jgl::Vector3Int tmp_pos = p_pos + jgl::Vector3Int(delta_x, -delta_y, tmp_prefab->levels[delta_x][tmp_prefab->size.y - (delta_y + 1)]);

			if (tmp_pos.z >= Chunk::C_LAYER_LENGTH)
				tmp_pos.z = Chunk::C_LAYER_LENGTH - 1;

			if (Engine::instance()->map()->content(tmp_pos) != tmp_prefab->composition[delta_x][tmp_prefab->size.y - (delta_y + 1)])
			{
				Engine::instance()->map()->place_node(tmp_pos, tmp_prefab->composition[delta_x][tmp_prefab->size.y - (delta_y + 1)]);
				_prefab_message << tmp_pos << tmp_prefab->composition[delta_x][tmp_prefab->size.y - (delta_y + 1)];
			}
		}
	}
}

void Prefab_item::_remove(jgl::Vector3Int p_pos)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	for (jgl::Int delta_x = 0; delta_x < tmp_prefab->size.x; delta_x++)
	{
		for (jgl::Int delta_y = 0; delta_y < tmp_prefab->size.y; delta_y++)
		{
			jgl::Vector3Int tmp_pos = p_pos + jgl::Vector3Int(delta_x, -delta_y, tmp_prefab->levels[delta_x][tmp_prefab->size.y - (delta_y + 1)]);
			if (tmp_pos.z >= Chunk::C_LAYER_LENGTH)
				tmp_pos.z = Chunk::C_LAYER_LENGTH - 1;

			Engine::instance()->map()->place_node(tmp_pos, -1);
			_prefab_message << tmp_pos << -1;
		}
	}
}

void Prefab_item::use(jgl::Vector3Int p_pos)
{
	_prefab_message.clear();

	_use(p_pos);

	if (_prefab_message.empty() == false)
		Client_manager::client()->send(_prefab_message);
}

void Prefab_item::use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	_prefab_message.clear();

	for (jgl::Int x = p_pos_start.x; x <= p_pos_end.x; x++)
	{
		for (jgl::Int y = p_pos_start.y; y <= p_pos_end.y; y++)
		{
			if ((x - p_pos_start.x) % tmp_prefab->size.x == 0 && (y - p_pos_start.y) % tmp_prefab->size.y == 0)
			{
				_use(jgl::Vector3Int(x, y, p_pos_start.z));
			}
		}
	}

	if (_prefab_message.empty() == false)
		Client_manager::client()->send(_prefab_message);
}

void Prefab_item::remove(jgl::Vector3Int p_pos)
{
	_prefab_message.clear();

	_remove(p_pos);

	if (_prefab_message.empty() == false)
		Client_manager::client()->send(_prefab_message);
}

void Prefab_item::remove(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	_prefab_message.clear();

	for (jgl::Int x = p_pos_start.x; x <= p_pos_end.x; x++)
	{
		for (jgl::Int y = p_pos_start.y; y <= p_pos_end.y; y++)
		{
			if ((x - p_pos_start.x) % tmp_prefab->size.x == 0 && (y - p_pos_start.y) % tmp_prefab->size.y == 0)
			{
				_remove(jgl::Vector3Int(x, y, p_pos_start.z));
			}
		}
	}

	if (_prefab_message.empty() == false)
		Client_manager::client()->send(_prefab_message);
}

jgl::Map<Flag_item::Color, jgl::Vector2Int> Flag_item::pos;

Flag_item::Flag_item(Flag_item::Color p_color) : Item(Item_type::Flag)
{
	color = p_color;
}

void Flag_item::use(jgl::Vector2Int p_pos)
{
	pos[color] = p_pos;
}

void Flag_item::remove(jgl::Vector2Int p_pos)
{
	if (pos.count(color) != 0 && p_pos == pos[color])
	{
		Flag_item::pos.erase(Flag_item::pos.find(color));
	}
}

jgl::Vector2Int Flag_item::sprite(Color p_color)
{
	return (jgl::Vector2Int(static_cast<jgl::Int>(p_color) + 1, 0));
}