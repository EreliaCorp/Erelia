#include "erelia.h"

void Player_interacter::_render()
{
	if ((jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down ||
		jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right) == jgl::Input_status::Down) && _editor_inventory->is_pointed() == false &&
		jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
	{
		jgl::Vector2Int tmp_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

		jgl::Vector2Int start = jgl::Vector2Int::compose_min(_selected_first_pos, tmp_pos);
		jgl::Vector2Int end = jgl::Vector2Int::compose_max(_selected_first_pos, tmp_pos) + 1;

		jgl::Vector2Int anchor = convert_world_to_screen(start);
		jgl::Vector2Int size = (end - start) * Node::size;

		jgl::draw_rectangle_color(jgl::Color(255, 255, 255, 120), anchor, size, _depth + 10);
	}
}

void Player_interacter::_on_geometry_change()
{
	_editor_inventory->set_geometry(0, _area);
}

void Player_interacter::_activate_editor_inventory()
{
	_editor_inventory->activate();
}
	
void Player_interacter::_desactivate_editor_inventory()
{
	_editor_inventory->desactivate();
}

Message modification_message(Server_message::Chunk_modification);

void Player_interacter::place_single_node(jgl::Vector3Int pos, jgl::Short value)
{
	modification_message.clear();

	if (Engine::instance()->map()->content(pos) != value)
	{
		Engine::instance()->map()->place_node(pos, value);
		modification_message << pos << value;
	}

	if (modification_message.empty() == false)
		Client_manager::client()->send(modification_message);
}

void Player_interacter::paint_node(jgl::Vector3Int p_pos, jgl::Short p_value)
{
	modification_message.clear();

	static jgl::Array<jgl::Vector3Int> pos_array;
	static jgl::Vector3Int delta[4] = {
		jgl::Vector3Int(1, 0, 0),
		jgl::Vector3Int(0, 1, 0),
		jgl::Vector3Int(-1, 0, 0),
		jgl::Vector3Int(0, -1, 0),
	};

	pos_array.clear();

	jgl::Short base_value = Engine::instance()->map()->content(p_pos);

	pos_array.push_back(p_pos);

	for (jgl::Size_t i = 0; i < pos_array.size() && pos_array.size() < Chunk::C_SIZE * Chunk::C_SIZE * 10; i++)
	{
		for (jgl::Size_t j = 0; j < 4; j++)
		{
			jgl::Vector3Int elem = pos_array[i] + delta[j];

			if (Engine::instance()->map()->content(elem) == base_value && pos_array.find(elem) == pos_array.end())
			{
				pos_array.push_back(elem);
			}
		}
	}

	for (jgl::Size_t i = 0; i < pos_array.size(); i++)
	{
		Engine::instance()->map()->place_node(pos_array[i], p_value);
		modification_message << pos_array[i] << p_value;
	}

	if (modification_message.empty() == false)
		Client_manager::client()->send(modification_message);
}

void Player_interacter::place_multiple_node(jgl::Vector3Int p_start, jgl::Vector3Int p_end, jgl::Short p_value)
{
	modification_message.clear();

	for (jgl::Int x = p_start.x; x <= p_end.x; x++)
	{
		for (jgl::Int y = p_start.y; y <= p_end.y; y++)
		{
			jgl::Vector3Int tmp_pos = jgl::Vector3Int(x, y, p_start.z);

			if (Engine::instance()->map()->content(tmp_pos) != p_value)
			{
				Engine::instance()->map()->place_node(tmp_pos, p_value);
				modification_message << tmp_pos << p_value;
			}
		}
	}

	if (modification_message.empty() == false)
		Client_manager::client()->send(modification_message);
}

void Player_interacter::place_circle_node(jgl::Vector3Int p_pos, jgl::Float p_radius, jgl::Short p_value)
{
	modification_message.clear();

	jgl::Vector3Int pos_start = p_pos - (p_radius + 1);
	jgl::Vector3Int pos_end = p_pos + (p_radius + 1);

	for (jgl::Int x = pos_start.x; x <= pos_end.x; x++)
	{
		for (jgl::Int y = pos_start.y; y <= pos_end.y; y++)
		{
			jgl::Vector3Int tmp_pos = jgl::Vector3Int(x, y, p_pos.z);
			if (Engine::instance()->map()->content(tmp_pos) != p_value && p_pos.distance(tmp_pos) <= p_radius)
			{
				Engine::instance()->map()->place_node(tmp_pos, p_value);
				modification_message << tmp_pos << p_value;
			}
		}
	}

	if (modification_message.empty() == false)
		Client_manager::client()->send(modification_message);
}

void Player_interacter::place_random_node(Remplace_data& p_random_data, jgl::Vector3Int p_pos, jgl::Float p_radius)
{
	modification_message.clear();

	jgl::Vector3Int pos_start = p_pos - (p_radius + 1);
	jgl::Vector3Int pos_end = p_pos + (p_radius + 1);

	for (jgl::Int x = pos_start.x; x <= pos_end.x; x++)
	{
		for (jgl::Int y = pos_start.y; y <= pos_end.y; y++)
		{
			jgl::Short replace_value = p_random_data.get_input();
			jgl::Short placing_value = p_random_data.get_output();

			jgl::Vector3Int tmp_pos = jgl::Vector3Int(x, y, p_pos.z);

			jgl::Short actual_value = Engine::instance()->map()->content(tmp_pos);

			if (actual_value == replace_value && actual_value != placing_value && p_pos.distance(tmp_pos) <= p_radius)
			{
				Engine::instance()->map()->place_node(tmp_pos, placing_value);
				modification_message << tmp_pos << placing_value;
			}
		}
	}

	if (modification_message.empty() == false)
		Client_manager::client()->send(modification_message);
}

void Player_interacter::_compose_pos(jgl::Vector3Int& p_actual, jgl::Vector3Int& p_start, jgl::Vector3Int& p_end)
{
	jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

	jgl::Vector2Int start = jgl::Vector2Int::compose_min(_selected_first_pos, tmp_second_pos);
	jgl::Vector2Int end = jgl::Vector2Int::compose_max(_selected_first_pos, tmp_second_pos);

	p_actual = jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level());
	p_start = jgl::Vector3Int(start.x, start.y, _editor_inventory->selected_level());
	p_end = jgl::Vector3Int(end.x, end.y, _editor_inventory->selected_level());
}

jgl::Bool Player_interacter::_update()
{
	if (Game_screen::instance()->gamemode() == Gamemode::Builder)
	{
		if (_editor_inventory->active() == false)
			_activate_editor_inventory();

		jgl::Input_status left_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left);
		jgl::Input_status right_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right);
		jgl::Input_status shift_key = jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift);

		Item* selected_item = _editor_inventory->selected_item();

		jgl::Vector3Int p_actual, p_start, p_end;

		if (Console_manager::instance()->console_entry_pointed() == true || _editor_inventory->is_pointed() == true || _editor_inventory->is_pointed() == true)
			return (false);

		if (left_button == jgl::Input_status::Pressed || right_button == jgl::Input_status::Pressed)
		{
			_selected_first_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());
		}
		if (shift_key == jgl::Input_status::Down)
		{
			if (left_button == jgl::Input_status::Release)
			{
				_compose_pos(p_actual, p_start, p_end);

				if (selected_item != nullptr && _brush_type == Brush_type::Brush_place)
				{
					if (selected_item->type == Item_type::Node)
						static_cast<Node_item*>(selected_item)->use(p_start, p_end);
					else if (selected_item->type == Item_type::Prefab)
						static_cast<Prefab_item*>(selected_item)->use(p_start, p_end);
				}
			}
			else if (right_button == jgl::Input_status::Release)
			{
				_compose_pos(p_actual, p_start, p_end);

				Map::send_edition_command(p_start, p_end, -1);
			}
		}
		else if (shift_key == jgl::Input_status::Up)
		{
			if (left_button == jgl::Input_status::Down)
			{
				_compose_pos(p_actual, p_start, p_end);

				if (_brush_type == Brush_type::Brush_replace)
				{
					place_random_node(_replace_data, p_actual, _brush_radius);
				}
				else if (selected_item != nullptr)
				{
					if (selected_item->type == Item_type::Node)
					{
						if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
							static_cast<Node_item*>(selected_item)->paint(p_actual, _brush_radius);
						else
							static_cast<Node_item*>(selected_item)->fill(p_actual);
					}
					else if (selected_item->type == Item_type::Prefab)
						static_cast<Prefab_item*>(selected_item)->use(p_actual);
				}
			}
			if (right_button == jgl::Input_status::Down)
			{
				_compose_pos(p_actual, p_start, p_end);

				if (selected_item->type == Item_type::Node)
				{
					Map::send_edition_command(p_actual, p_actual, -1);
				}
				else if (selected_item->type == Item_type::Prefab)
					static_cast<Prefab_item*>(selected_item)->remove(p_actual);
			}
		}
		

		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::F7) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->save();
		}

		return (false);
	}
	else if (Game_screen::instance()->gamemode() == Gamemode::Adventure)
	{
		if (_editor_inventory->active() == true)
			_desactivate_editor_inventory();
	}

	return (false);
}

extern Message modification_message;

void Player_interacter::_parse_string_block_data(jgl::Array<Block_replace_data>& p_array, jgl::String p_text)
{
	static jgl::Array<jgl::String> tab;

	p_text.split(tab, "/");

	for (jgl::Size_t i = 0; i < tab.size(); i += 2)
	{
		p_array.push_back(Block_replace_data(jgl::stoi(tab[i + 1]), jgl::stof(tab[i]) * 100));
	}
}

void Player_interacter::set_brush_type_info(jgl::String p_brush_type_info)
{
	_replace_data.clear();

	static jgl::Array<jgl::String> tab;

	p_brush_type_info.split(tab, " ");

	_parse_string_block_data(_replace_data.input, tab[0]);
	_parse_string_block_data(_replace_data.output, tab[1]);
}

Player_interacter::Player_interacter(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{
	_editor_inventory = new Editor_inventory(this);
	_editor_inventory->set_depth(_depth + 100);
	_editor_inventory->desactivate();
}