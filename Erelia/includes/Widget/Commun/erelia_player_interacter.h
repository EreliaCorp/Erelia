#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_graphical_widget.h"
#include "Widget/Commun/erelia_editor_inventory.h"

class Player_interacter : public Graphical_widget
{
public:
	enum class Brush_type
	{
		Brush_place = 0,
		Brush_replace = 1,
		Brush_place_wall = 2
	};

	struct Block_replace_data
	{
		jgl::Short value;
		jgl::Float percent;

		Block_replace_data(jgl::Short p_value = -1, jgl::Float p_percent = 100) {
			value = p_value;
			percent = p_percent;
		}
	};
	struct Remplace_data
	{
		jgl::Array<Block_replace_data> input;
		jgl::Array<Block_replace_data> output;

		void clear()
		{
			input.clear();
			output.clear();
		}

		jgl::Short get_input()
		{
			jgl::Int range = jgl::generate_nbr(0, 10000);

			for (jgl::Size_t i = 0; i < input.size(); i++)
			{
				range -= input[i].percent;

				if (range <= 0)
					return (input[i].value);
			}
			return (-1);
		}

		jgl::Short get_output()
		{
			jgl::Int range = jgl::generate_nbr(0, 10000);

			for (jgl::Size_t i = 0; i < output.size(); i++)
			{
				range -= output[i].percent;

				if (range <= 0)
					return (output[i].value);
			}
			return (-1);
		}
	};

private:
	Editor_inventory* _editor_inventory;

	jgl::Float _brush_radius = 0;
	Brush_type _brush_type = Brush_type::Brush_place;

	Remplace_data _replace_data;

	jgl::Vector2Int _selected_first_pos;

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();
	void _activate_editor_inventory();
	void _desactivate_editor_inventory();

	void _parse_string_block_data(jgl::Array<Block_replace_data>& p_array, jgl::String p_text);

	jgl::Short _get_input_type();
	jgl::Short _get_output_type();

	void _compose_pos(jgl::Vector3Int& p_actual, jgl::Vector3Int& p_start, jgl::Vector3Int& p_end);

public:
	Player_interacter(jgl::Widget* p_parent);
	void set_brush_radius(jgl::Size_t p_brush_radius) { _brush_radius = p_brush_radius; }
	void set_brush_type(Brush_type p_brush_type) { _brush_type = p_brush_type; }
	void set_brush_type_info(jgl::String p_brush_type_info);

	static void place_multiple_node(jgl::Vector3Int p_start, jgl::Vector3Int p_end, jgl::Short p_value);
	static void place_single_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void paint_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void paint_wall_node(jgl::Vector3Int p_pos, jgl::Short p_value);
	static void place_circle_node(jgl::Vector3Int p_pos, jgl::Float p_radius, jgl::Short p_value);
	static void place_random_node(Remplace_data& p_random_data, jgl::Vector3Int p_pos, jgl::Float p_radius);
};