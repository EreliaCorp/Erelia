#include "erelia.h"

Node_item::Node_item(jgl::Short p_value) : Item(Item_type::Node)
{
	value = p_value;
}

void Node_item::use(Map* p_map, jgl::Vector3Int p_pos)
{
	p_map->place_node(p_pos, value);
}

Prefab_item::Prefab_item(jgl::Short p_value) : Item(Item_type::Prefab)
{
	value = p_value;
}

void Prefab_item::use(class Map* p_map, jgl::Vector3Int p_pos)
{
	Prefab* tmp_prefab = g_prefab_array[value];

	for (jgl::Int x = 0; x < tmp_prefab->size.x; x++)
	{
		for (jgl::Int y = 0; y < tmp_prefab->size.y; y++)
		{
			jgl::Vector3Int tmp_pos = p_pos + jgl::Vector3Int(x, -y, tmp_prefab->levels[x][tmp_prefab->size.y - (y + 1)]);
			if (tmp_pos.z >= Chunk::C_LAYER_LENGTH)
				tmp_pos.z = Chunk::C_LAYER_LENGTH - 1;

			p_map->place_node(tmp_pos, tmp_prefab->composition[x][tmp_prefab->size.y - (y + 1)]);
		}
	}
}
