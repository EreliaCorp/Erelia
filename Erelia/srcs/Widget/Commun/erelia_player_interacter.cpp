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
	static jgl::Map<jgl::Vector3Int, jgl::Bool> pos_array_found;
	static jgl::Vector3Int delta[4] = {
		jgl::Vector3Int(1, 0, 0),
		jgl::Vector3Int(0, 1, 0),
		jgl::Vector3Int(-1, 0, 0),
		jgl::Vector3Int(0, -1, 0),
	};

	pos_array.clear();
	pos_array_found.clear();

	jgl::Short base_value = Engine::instance()->map()->content(p_pos);

	pos_array.push_back(p_pos);

	for (jgl::Size_t i = 0; i < pos_array.size() && pos_array.size() < Chunk::C_SIZE * Chunk::C_SIZE * 10; i++)
	{
		if (Engine::instance()->map()->content(pos_array[i]) == base_value)
		{
			for (jgl::Size_t j = 0; j < 4; j++)
			{
				jgl::Vector3Int elem = pos_array[i] + delta[j];

				if (Engine::instance()->map()->content(elem) == base_value && pos_array_found[elem] == false)
				{
					pos_array.push_back(elem);
					pos_array_found[elem] = true;
				}
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

unsigned char reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

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

static jgl::Map<jgl::Uchar, jgl::Short> delta_map_bit_value_result = {
	{0, -1},
	{1, 33},
	{2, 98},
	{3, 98},
	{4, 34},
	{5, 98},
	{6, 98},
	{7, 98},
	{8, 35},
	{9, 35},
	{10, -2},
	{11, 99},
	{12, -2},
	{13, -2},
	{14, -2},
	{15, 99},
	{16, 64},
	{17, -2},
	{18, -2},
	{19, -2},
	{20, 64},
	{21, -2},
	{22, 96},
	{23, 96},
	{24, -2},
	{25, -2},
	{26, -2},
	{27, -2},
	{28, -2},
	{29, -2},
	{30, -2},
	{31, -1},
	{32, 65},
	{33, 35},
	{34, -2},
	{35, -2},
	{36, -2},
	{37, -2},
	{38, -2},
	{39, -2},
	{40, 35},
	{41, 35},
	{42, -2},
	{43, 99},
	{44, -2},
	{45, -2},
	{46, -2},
	{47, 99},
	{48, -2},
	{49, -2},
	{50, -2},
	{51, -2},
	{52, -2},
	{53, -2},
	{54, -2},
	{55, -2},
	{56, -2},
	{57, -2},
	{58, -2},
	{59, -2},
	{60, -2},
	{61, -2},
	{62, -2},
	{63, -2},
	{64, 1},
	{65, -2},
	{66, -2},
	{67, -2},
	{68, -2},
	{69, -2},
	{70, -2},
	{71, -2},
	{72, -2},
	{73, -2},
	{74, -2},
	{75, -2},
	{76, -2},
	{77, -2},
	{78, -2},
	{79, -2},
	{80, -2},
	{81, -2},
	{82, -2},
	{83, -2},
	{84, -2},
	{85, -2},
	{86, -2},
	{87, -2},
	{88, -2},
	{89, -2},
	{90, -2},
	{91, -2},
	{92, -2},
	{93, -2},
	{94, -2},
	{95, -2},
	{96, 1},
	{97, -2},
	{98, -2},
	{99, -2},
	{100, -2},
	{101, -2},
	{102, -2},
	{103, -2},
	{104, 3},
	{105, 3},
	{106, -2},
	{107, -1},
	{108, -2},
	{109, -2},
	{110, -2},
	{111, -2},
	{112, -2},
	{113, -2},
	{114, -2},
	{115, -2},
	{116, -2},
	{117, -2},
	{118, -2},
	{119, -2},
	{120, -2},
	{121, -2},
	{122, -2},
	{123, -2},
	{124, -2},
	{125, -2},
	{126, -2},
	{127, -2},
	{128, 66},
	{129, -2},
	{130, -2},
	{131, -2},
	{132, 64},
	{133, -2},
	{134, -2},
	{135, -2},
	{136, -2},
	{137, -2},
	{138, -2},
	{139, -2},
	{140, -2},
	{141, -2},
	{142, -2},
	{143, -2},
	{144, 64},
	{145, -2},
	{146, -2},
	{147, -2},
	{148, 64},
	{149, -2},
	{150, 96},
	{151, 96},
	{152, -2},
	{153, -2},
	{154, -2},
	{155, -2},
	{156, -2},
	{157, -2},
	{158, -2},
	{159, -2},
	{160, 1},
	{161, -2},
	{162, -2},
	{163, -2},
	{164, -2},
	{165, -2},
	{166, -2},
	{167, -2},
	{168, -2},
	{169, -2},
	{170, -2},
	{171, -2},
	{172, -2},
	{173, -2},
	{174, -2},
	{175, -2},
	{176, -2},
	{177, -2},
	{178, -2},
	{179, -2},
	{180, -2},
	{181, -2},
	{182, -2},
	{183, -2},
	{184, -2},
	{185, -2},
	{186, -2},
	{187, -2},
	{188, -2},
	{189, -2},
	{190, -2},
	{191, -2},
	{192, 1},
	{193, -2},
	{194, -2},
	{195, -2},
	{196, -2},
	{197, -2},
	{198, -2},
	{199, -2},
	{200, -2},
	{201, -2},
	{202, -2},
	{203, -2},
	{204, -2},
	{205, -2},
	{206, -2},
	{207, -2},
	{208, 0},
	{209, -2},
	{210, -2},
	{211, -2},
	{212, 0},
	{213, -2},
	{214, -1},
	{215, -2},
	{216, -2},
	{217, -2},
	{218, -2},
	{219, -2},
	{220, -2},
	{221, -2},
	{222, -2},
	{223, -2},
	{224, 1},
	{225, 3},
	{226, -2},
	{227, -2},
	{228, 0},
	{229, -2},
	{230, -2},
	{231, -2},
	{232, 3},
	{233, 3},
	{234, -2},
	{235, -1},
	{236, -2},
	{237, -2},
	{238, -2},
	{239, -2},
	{240, 0},
	{241, -2},
	{242, -2},
	{243, -2},
	{244, 0},
	{245, -2},
	{246, -1},
	{247, -2},
	{248, -1},
	{249, -2},
	{250, -2},
	{251, -2},
	{252, -2},
	{253, -2},
	{254, -2},
	{255, -2}
};

void Player_interacter::paint_wall_node(jgl::Vector3Int p_pos, jgl::Short p_value)
{
	modification_message.clear();

	static jgl::Array<jgl::Vector3Int> pos_array;
	static jgl::Map<jgl::Vector3Int, jgl::Bool> pos_array_found;
	static jgl::Array<Place_wall_data> result;
	static jgl::Vector3Int delta[8] = {
		jgl::Vector3Int(-1, -1, 0),
		jgl::Vector3Int(0, -1, 0),
		jgl::Vector3Int(1, -1, 0),

		jgl::Vector3Int(-1, 0, 0),
		jgl::Vector3Int(1, 0, 0),

		jgl::Vector3Int(-1, 1, 0),
		jgl::Vector3Int(0, 1, 0),
		jgl::Vector3Int(1, 1, 0)
	};

	pos_array.clear();
	pos_array_found.clear();
	result.clear();

	jgl::Short base_value = Engine::instance()->map()->content(p_pos);

	if (base_value == -1)
		return;
	pos_array.push_back(p_pos);

	for (jgl::Size_t i = 0; i < pos_array.size(); i++)
	{
		jgl::Uchar bit_value = 0;

		for (jgl::Size_t j = 0; j < 8; j++)
		{
			jgl::Vector3Int elem = pos_array[i] + delta[j];
			jgl::Short tmp_value = Engine::instance()->map()->content(elem);

			bit_value *= 2;
			bit_value += (tmp_value == base_value ? 0 : 1);

			if (tmp_value == base_value && pos_array_found[elem] == false)
			{
				pos_array.push_back(elem);
				pos_array_found[elem] = true;
			}
		}

		if (delta_map_bit_value_result[bit_value] != -2)
		{
			jgl::Short tmp_value = (delta_map_bit_value_result[bit_value] == -1 ? -1 : p_value + delta_map_bit_value_result[bit_value]);
			result.push_back(Place_wall_data(pos_array[i], tmp_value));
		}
		else
		{
			jgl::cout << "Bit_value [" << static_cast<jgl::Int>(bit_value) << "]" << jgl::endl;
			jgl::Uchar to_print = reverse(bit_value);
			for (jgl::Size_t y = 0; y < 3; y++)
			{
				for (jgl::Size_t x = 0; x < 3; x++)
				{
					if (x == 1 && y == 1)
					{
						jgl::cout << "[0]";
					}
					else
					{
						jgl::cout << "[" << ((to_print & 1) == 1 ? ' ' : 'X') << "]";
						to_print /= 2;
					}
				}
				jgl::cout << jgl::endl;
			}
			jgl::cout << jgl::endl;
		}
	}

	for (jgl::Size_t i = 0; i < result.size(); i++)
	{
		Engine::instance()->map()->place_node(result[i].pos, result[i].value);
		modification_message << result[i].pos << result[i].value;
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
					if (_brush_type == Brush_type::Brush_place)
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
			}
			else if (left_button == jgl::Input_status::Release)
			{
				_compose_pos(p_actual, p_start, p_end);

				if (_brush_type == Brush_type::Brush_place_wall && selected_item != nullptr && selected_item->type == Item_type::Node && Engine::instance()->map()->content(p_actual) != -1)
				{
					static_cast<Node_item*>(selected_item)->paint_wall(p_actual);
				}
			}
			if (right_button == jgl::Input_status::Down)
			{
				_compose_pos(p_actual, p_start, p_end);

				if (selected_item == nullptr || selected_item->type == Item_type::Node)
				{
					if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
					{
						Map::send_edition_command(p_actual, p_actual, -1);
					}
					else
					{
						paint_node(p_actual, -1);
					}
				}
				else if (selected_item->type == Item_type::Prefab)
					static_cast<Prefab_item*>(selected_item)->remove(p_actual);
			}
		}
		

		if (Server_manager::instance() != nullptr && jgl::Application::active_application()->keyboard().get_key(jgl::Key::F7) == jgl::Input_status::Release)
		{
			Server_manager::instance()->send_global_message("[Systm.] : Saving server's map started - This can take a while");
			Engine::instance()->map()->save();
			Server_manager::instance()->send_global_message("[Systm.] : Saving server's map completed");
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