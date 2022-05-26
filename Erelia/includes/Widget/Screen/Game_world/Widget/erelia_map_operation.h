#pragma once

#include "network/erelia_network_definition.h"
#include "widget/screen/game_world/Widget/erelia_player_interacter.h"

class Map_operation
{
public:
	struct Place_wall_data
	{
		jgl::Vector3Int pos;
		jgl::Short value;

		Place_wall_data(jgl::Vector3Int p_pos = 0, jgl::Short p_value = 0)
		{
			pos = p_pos;
			value = p_value;
		}
	};

private:
	static Message _modification_message;
	static Message _teleporter_modification_message;

public:
	static void place_multiple_node(jgl::Vector3Int p_start, jgl::Vector3Int p_end, jgl::Short p_value);
	static void place_single_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void paint_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void paint_wall_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void place_circle_node(jgl::Vector3Int p_pos, jgl::Float p_radius, jgl::Short p_value);
	static void place_random_node(Player_interacter::Remplace_data& p_random_data, jgl::Vector3Int p_pos, jgl::Float p_radius);

	static void place_teleporter(jgl::Vector2Int p_pos, jgl::Int p_value);

	static void paint_wall_node_standalone(jgl::Array<Map_operation::Place_wall_data>& result, jgl::Vector3Int p_pos, jgl::Short p_value);
};