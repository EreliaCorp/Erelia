#include "erelia.h"

Message prefab_message(Server_message::Chunk_modification);

Node_item::Node_item(jgl::Short p_value) : Item(Item_type::Node)
{
	value = p_value;
}

void Node_item::use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Player_interacter::place_multiple_node(p_pos_start, p_pos_end, value);
}

void Node_item::fill(jgl::Vector3Int p_pos)
{
	Player_interacter::paint_node(p_pos, value);
}

void Node_item::paint(jgl::Vector3Int p_pos, jgl::Size_t p_radius)
{
	Player_interacter::place_circle_node(p_pos, p_radius, value);

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
				prefab_message << tmp_pos << tmp_prefab->composition[delta_x][tmp_prefab->size.y - (delta_y + 1)];
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
			prefab_message << tmp_pos << -1;
		}
	}
}

void Prefab_item::use(jgl::Vector3Int p_pos)
{
	prefab_message.clear();

	_use(p_pos);

	if (prefab_message.empty() == false)
		Client_manager::client()->send(prefab_message);
}

void Prefab_item::use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	prefab_message.clear();

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

	if (prefab_message.empty() == false)
		Client_manager::client()->send(prefab_message);
}

void Prefab_item::remove(jgl::Vector3Int p_pos)
{
	prefab_message.clear();

	_remove(p_pos);

	if (prefab_message.empty() == false)
		Client_manager::client()->send(prefab_message);
}

void Prefab_item::remove(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	prefab_message.clear();

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

	if (prefab_message.empty() == false)
		Client_manager::client()->send(prefab_message);
}
