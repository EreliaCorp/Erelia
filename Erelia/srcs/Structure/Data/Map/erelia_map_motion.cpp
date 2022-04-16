#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_entity.h"
#include "Structure/Atlas/erelia_path_atlas.h"

jgl::Vector2Int direction_value[8] = {
	jgl::Vector2Int(-1, -1),
	jgl::Vector2Int(0, -1),
	jgl::Vector2Int(1, -1),
	jgl::Vector2Int(1, 0),
	jgl::Vector2Int(-1, 0),
	jgl::Vector2Int(-1, 1),
	jgl::Vector2Int(0, 1),
	jgl::Vector2Int(1, 1),
};
jgl::Vector2Int axis_direction_value[4] = {
	jgl::Vector2Int(0, -1),
	jgl::Vector2Int(1, 0),
	jgl::Vector2Int(-1, 0),
	jgl::Vector2Int(0, 1)
};
jgl::Int direction_mask[8] = {
	Node::NORTH_WALKABLE | Node::WEST_WALKABLE,
	Node::NORTH_WALKABLE,
	Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
	Node::EAST_WALKABLE,
	Node::WEST_WALKABLE,
	Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
	Node::SOUTH_WALKABLE,
	Node::SOUTH_WALKABLE | Node::EAST_WALKABLE
};
jgl::Int rev_direction_mask[8] = {
	Node::SOUTH_WALKABLE | Node::EAST_WALKABLE,
	Node::SOUTH_WALKABLE,
	Node::SOUTH_WALKABLE | Node::WEST_WALKABLE,
	Node::WEST_WALKABLE,
	Node::EAST_WALKABLE,
	Node::NORTH_WALKABLE | Node::EAST_WALKABLE,
	Node::NORTH_WALKABLE,
	Node::NORTH_WALKABLE | Node::WEST_WALKABLE
};

jgl::Bool Map::can_acces(jgl::Vector2Int p_start, jgl::Vector2Int p_direction)
{
	jgl::Vector2 p_destination = p_start + p_direction;

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
		if (pos_value >= 0)
			value &= g_node_array[pos_value]->obstacle;
		if (destination_pos_value >= 0)
			destination_value &= g_node_array[destination_pos_value]->obstacle;
	}

	if ((value & direction_mask[index]) != direction_mask[index] || (destination_value & rev_direction_mask[index]) != rev_direction_mask[index])
		return (false);
	return (true);
}

void Map::_calc_result(const Map::AStar_node* destination, jgl::Array<jgl::Vector2Int>& p_path)
{
	p_path.clear();
	while (destination->parent != nullptr)
	{
		p_path.push_front(destination->delta);
		destination = destination->parent;
	}
}

const Map::AStar_node* Map::_found_closest_node(jgl::Array<Map::AStar_node>& p_to_calc, jgl::Size_t p_first_index)
{
	Map::AStar_node* result = nullptr;
	for (jgl::Size_t i = p_first_index; i < p_to_calc.size(); i++)
	{
		if (result == nullptr || result->distance > p_to_calc[i].distance)
		{
			result = &p_to_calc[i];
		}
	}
	return (result);
}

void Map::find_path(jgl::Array<jgl::Vector2Int>& p_path, jgl::Vector2Int p_source, jgl::Vector2Int p_destination, jgl::Int p_max_length)
{
	static jgl::Map<jgl::Vector2Int, jgl::Bool> checked_map;
	static jgl::Array<AStar_node> to_calc;

	checked_map.clear();
	to_calc.clear();

	to_calc.push_back(Map::AStar_node(p_source.distance(p_destination), p_source, 0, nullptr, 0));
	checked_map[p_source] = true;

	for (jgl::Size_t i = 0; i < to_calc.size(); i++)
	{
		const Map::AStar_node* tmp_node = _found_closest_node(to_calc, i);

		if (tmp_node->pos == p_destination)
		{
			THROW_INFORMATION("Path found from [" + p_source.text() + "] to [" + p_destination.text() + "]");
			_calc_result(tmp_node, p_path);
			return;
		}
		for (jgl::Size_t j = 0; j < 4; j++)
		{
			jgl::Vector2Int tmp_destination = tmp_node->pos + axis_direction_value[j];
			if (checked_map[tmp_destination] == false &&
				can_acces(tmp_node->pos, axis_direction_value[j]) == true)
			{
				checked_map[tmp_destination] = true;
				to_calc.push_back(Map::AStar_node(tmp_destination.distance(p_destination), tmp_destination, axis_direction_value[j], tmp_node, tmp_node->path_len + 1));
			}
		}
	}

	THROW_INFORMATION("No path found from [" + p_source.text() + "] to [" + p_destination.text() + "]");
	p_path.clear();
	return;
}

jgl::Array<jgl::Vector2Int> Map::find_path(jgl::Vector2Int p_source, jgl::Vector2Int p_destination, jgl::Int p_max_length)
{
	jgl::Array<jgl::Vector2Int> result;

	find_path(result, p_source, p_destination, p_max_length);

	return result;
}