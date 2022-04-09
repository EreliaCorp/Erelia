#pragma once

#include "network/erelia_network_definition.h"
#include "widget/screen/game_world/Widget/erelia_player_interacter.h"

class Map_operation
{
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
};