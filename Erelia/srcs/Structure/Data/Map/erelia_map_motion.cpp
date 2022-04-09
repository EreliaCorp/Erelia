#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_entity.h"
#include "Structure/Atlas/erelia_path_atlas.h"

jgl::Bool Map::can_move(Entity* p_entity, jgl::Vector2 p_start, jgl::Vector2 p_direction)
{
	if (chunk(convert_world_to_chunk(p_start + p_direction)) == nullptr)
		return (false);

	jgl::Vector2 p_destination = p_start + p_direction;
	static jgl::Vector2Int direction_value[8] = {
		jgl::Vector2Int(-1, -1),
		jgl::Vector2Int(0, -1),
		jgl::Vector2Int(1, -1),
		jgl::Vector2Int(1, 0),
		jgl::Vector2Int(-1, 0),
		jgl::Vector2Int(-1, 1),
		jgl::Vector2Int(0, 1),
		jgl::Vector2Int(1, 1),
	};
	static jgl::Int direction_mask[8] = {
		Node::NORTH_WALKABLE | Node::WEST_WALKABLE,
		Node::NORTH_WALKABLE,
		Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
		Node::EAST_WALKABLE,
		Node::WEST_WALKABLE,
		Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
		Node::SOUTH_WALKABLE,
		Node::SOUTH_WALKABLE | Node::EAST_WALKABLE
	};
	static jgl::Int rev_direction_mask[8] = {
		Node::SOUTH_WALKABLE | Node::EAST_WALKABLE,
		Node::SOUTH_WALKABLE,
		Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
		Node::WEST_WALKABLE,
		Node::EAST_WALKABLE,
		Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
		Node::NORTH_WALKABLE,
		Node::NORTH_WALKABLE | Node::WEST_WALKABLE
	};

	jgl::Size_t index = 0;
	for (index = 0; index < 8 && direction_value[index] != p_direction; index++) {}

	jgl::Short value = Node::WALKABLE;
	jgl::Short destination_value = Node::WALKABLE;
	for (jgl::Size_t i = 0; i < Chunk::C_LAYER_LENGTH; i++)
	{
		jgl::Short pos_value = content(p_start, i);
		jgl::Short destination_pos_value = content(p_destination, i);

		if (i == 0 && pos_value == -1)
			value = Node::OBSTACLE;
		if (i == 0 && destination_pos_value == -1)
			destination_value = Node::OBSTACLE;
		if (pos_value != -1)
			value &= g_node_array[pos_value]->obstacle;
		if (destination_pos_value != -1)
			destination_value &= g_node_array[destination_pos_value]->obstacle;
	}

	if ((value & direction_mask[index]) != direction_mask[index] || (destination_value & rev_direction_mask[index]) != rev_direction_mask[index])
		return (false);
	return (true);
}

void Map::find_path(jgl::Array<jgl::Vector2Int>& p_path, jgl::Vector2Int p_source, jgl::Vector2Int p_destination, jgl::Int p_max_length)
{
	p_path.clear();
}