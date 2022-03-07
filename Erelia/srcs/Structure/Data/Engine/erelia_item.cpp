#include "erelia.h"

Node_item::Node_item(jgl::Short p_value) : Item(Item_type::Node)
{
	value = p_value;
}

void Node_item::use(jgl::Vector3Int p_pos_start, jgl::Vector3Int p_pos_end)
{
	Map::send_edition_command(p_pos_start, p_pos_end, value);
}

Prefab_item::Prefab_item(jgl::Short p_value) : Item(Item_type::Prefab)
{
	value = p_value;
}

void Prefab_item::use(jgl::Vector3Int p_pos)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	static Message msg(Server_message::Chunk_modification);

	msg.clear();

	for (jgl::Int x = 0; x < tmp_prefab->size.x; x++)
	{
		for (jgl::Int y = 0; y < tmp_prefab->size.y; y++)
		{
			jgl::Vector3Int tmp_pos = p_pos + jgl::Vector3Int(x, -y, tmp_prefab->levels[x][tmp_prefab->size.y - (y + 1)]);
			if (tmp_pos.z >= Chunk::C_LAYER_LENGTH)
				tmp_pos.z = Chunk::C_LAYER_LENGTH - 1;

			Engine::instance()->map()->place_node(tmp_pos, tmp_prefab->composition[x][tmp_prefab->size.y - (y + 1)]);
			msg << tmp_pos << tmp_prefab->composition[x][tmp_prefab->size.y - (y + 1)];
		}
	}

	Client_manager::client()->send(msg);
}
