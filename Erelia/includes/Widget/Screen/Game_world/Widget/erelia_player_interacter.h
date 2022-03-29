#pragma once

#include "jgl.h"

#include "network/erelia_network_definition.h"
#include "widget/Abstract_widget/erelia_overworld_widget.h"
#include "widget/Abstract_widget/erelia_abstract_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_editor_inventory.h"

class Player_interacter : public Overworld_widget, public Abstract_manager
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

	enum class Mode
	{
		Adventure,
		Builder,
		Area_builder
	};
	enum class Event
	{
		Go_adventure,
		Go_builder,
		Go_area_builder
	};
	struct Context
	{
		jgl::Int monster_value = -1;

		jgl::Float brush_radius = 0;
		Brush_type brush_type = Brush_type::Brush_place;

		Remplace_data replace_data;

		jgl::Vector2Int selected_first_pos;
	};
private:
	Editor_inventory* _editor_inventory;

	jgl::Publisher<Event, Context>* _publisher;
	jgl::State_machine<Mode>* _state_machine;

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();

	void _parse_string_block_data(jgl::Array<Block_replace_data>& p_array, jgl::String p_text);

	void _receive_brush_size_change(Message& p_msg);
	void _receive_brush_type_change(Message& p_msg);
	void _receive_brush_type_data_change(Message& p_msg);
	void _receive_monster_area_value(Message& p_msg);

	void _initialize_server();
	void _initialize_client();

public:
	Player_interacter(jgl::Widget* p_parent);

	Editor_inventory* editor_inventory() {return (_editor_inventory);}
	jgl::Publisher<Event, Context>* publisher() {return (_publisher);}
	jgl::State_machine<Mode>* state_machine() { return (_state_machine);}

	void compose_pos(jgl::Vector2Int& p_actual, jgl::Vector2Int& p_start, jgl::Vector2Int& p_end);
	void compose_pos(jgl::Vector3Int& p_actual, jgl::Vector3Int& p_start, jgl::Vector3Int& p_end);

	void set_brush_radius(jgl::Size_t p_brush_radius) { _publisher->context()->brush_radius = p_brush_radius; }
	void set_brush_type(Brush_type p_brush_type) { _publisher->context()->brush_type = p_brush_type; }
	void set_brush_type_info(jgl::String p_brush_type_info);
	void set_monster_value(jgl::Int p_value) { _publisher->context()->monster_value = p_value; }
};