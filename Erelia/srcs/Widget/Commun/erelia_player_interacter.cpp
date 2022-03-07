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

jgl::Bool Player_interacter::_update()
{
	if (Game_screen::instance()->gamemode() == Gamemode::Builder)
	{
		if (_editor_inventory->active() == false)
			_activate_editor_inventory();

		if (Console_manager::instance()->console_entry_pointed() == true || _editor_inventory->is_pointed() == true)
			return (false);

		if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Pressed ||
			jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right) == jgl::Input_status::Pressed)
		{
			_selected_first_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());
		}
		if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Release && _editor_inventory->is_pointed() == false &&
			jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
		{
			Item* selected_item = _editor_inventory->selected_item();

			if (selected_item != nullptr)
			{
				jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

				jgl::Vector2Int start = jgl::Vector2Int::compose_min(_selected_first_pos, tmp_second_pos);
				jgl::Vector2Int end = jgl::Vector2Int::compose_max(_selected_first_pos, tmp_second_pos);

				if (selected_item->type == Item_type::Node)
					static_cast<Node_item*>(selected_item)->use(jgl::Vector3Int(start.x, start.y, _editor_inventory->selected_level()), jgl::Vector3Int(end.x, end.y, _editor_inventory->selected_level()));
			}
		}
		if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right) == jgl::Input_status::Release && _editor_inventory->is_pointed() == false &&
			jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Down)
		{
			jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

			jgl::Vector2Int start = jgl::Vector2Int::compose_min(_selected_first_pos, tmp_second_pos);
			jgl::Vector2Int end = jgl::Vector2Int::compose_max(_selected_first_pos, tmp_second_pos);

			jgl::Vector3Int pos_start = jgl::Vector3Int(start.x, start.y, _editor_inventory->selected_level());
			jgl::Vector3Int pos_end = jgl::Vector3Int(end.x, end.y, _editor_inventory->selected_level());

			Map::send_edition_command(pos_start, pos_end, -1);

		}
		if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down && _editor_inventory->is_pointed() == false &&
			jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Up)
		{
			Item* selected_item = _editor_inventory->selected_item();

			if (selected_item != nullptr)
			{
				jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

				if (selected_item->type == Item_type::Node)
					static_cast<Node_item*>(selected_item)->use(jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level()), jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level()));
				else if (selected_item->type == Item_type::Prefab)
					static_cast<Prefab_item*>(selected_item)->use(jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level()));
			}
		}
		if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right) == jgl::Input_status::Down && _editor_inventory->is_pointed() == false &&
			jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift) == jgl::Input_status::Up)
		{
			jgl::Vector2Int tmp_second_pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());
			jgl::Vector3Int pos = jgl::Vector3Int(tmp_second_pos.x, tmp_second_pos.y, _editor_inventory->selected_level());
			Map::send_edition_command(pos, pos, -1);
		}


		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::F7) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->save();
		}

		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_1) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->set_node_size(4);
		}
		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_2) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->set_node_size(8);
		}
		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_3) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->set_node_size(16);
		}
		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_4) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->set_node_size(32);
		}
		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_5) == jgl::Input_status::Release)
		{
			Engine::instance()->map()->set_node_size(64);
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

Player_interacter::Player_interacter(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{
	_editor_inventory = new Editor_inventory(this);
	_editor_inventory->set_depth(_depth + 100);
	_editor_inventory->desactivate();
}