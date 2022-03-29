#include "widget/Screen/game_world/Widget/erelia_player_interacter_activity.h"
#include "widget/Screen/Game_world/Widget/erelia_map_operation.h"
#include "Widget/Commun/erelia_console_manager.h"
#include "structure/Data/Engine/erelia_engine.h"

namespace Player_interact_activity
{
	Builder::Builder(Player_interacter* p_interacter) : Abstract_activity(p_interacter)
	{

	}

	void Builder::execute()
	{
		jgl::Input_status left_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left);
		jgl::Input_status right_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right);
		jgl::Input_status shift_key = jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift);

		Item* selected_item = _interacter->editor_inventory()->selected_item();

		jgl::Vector3Int p_actual, p_start, p_end;

		if (Console_manager::instance()->console_entry_pointed() == true || _interacter->editor_inventory()->is_pointed() == true || _interacter->editor_inventory()->is_pointed() == true)
			return ;

		if (left_button == jgl::Input_status::Pressed || right_button == jgl::Input_status::Pressed)
		{
			_interacter->publisher()->context()->selected_first_pos = _interacter->convert_screen_to_world(jgl::Application::active_application()->mouse().pos());
		}
		if (shift_key == jgl::Input_status::Down)
		{
			if (left_button == jgl::Input_status::Release)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (selected_item != nullptr && _interacter->publisher()->context()->brush_type == Player_interacter::Brush_type::Brush_place)
				{
					if (selected_item->type == Item_type::Node)
						static_cast<Node_item*>(selected_item)->use(p_start, p_end);
					else if (selected_item->type == Item_type::Prefab)
						static_cast<Prefab_item*>(selected_item)->use(p_start, p_end);
				}
			}
			else if (right_button == jgl::Input_status::Release)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				Map_operation::place_multiple_node(p_start, p_end, -1);
			}
		}
		else if (shift_key == jgl::Input_status::Up)
		{
			if (left_button == jgl::Input_status::Down)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (_interacter->publisher()->context()->brush_type == Player_interacter::Brush_type::Brush_replace)
				{
					Map_operation::place_random_node(_interacter->publisher()->context()->replace_data, p_actual, _interacter->publisher()->context()->brush_radius);
				}
				else if (selected_item != nullptr)
				{
					if (_interacter->publisher()->context()->brush_type == Player_interacter::Brush_type::Brush_place)
					{
						if (selected_item->type == Item_type::Node)
						{
							if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
								static_cast<Node_item*>(selected_item)->paint(p_actual, _interacter->publisher()->context()->brush_radius);
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
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (_interacter->publisher()->context()->brush_type == Player_interacter::Brush_type::Brush_place_wall &&
					selected_item != nullptr &&
					selected_item->type == Item_type::Node &&
					Engine::instance()->map()->content(p_actual) != -1)
				{
					static_cast<Node_item*>(selected_item)->paint_wall(p_actual);
				}
			}
			if (right_button == jgl::Input_status::Down)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (selected_item == nullptr || selected_item->type == Item_type::Node)
				{
					if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
					{
						Map_operation::place_multiple_node(p_actual, p_actual, -1);
					}
					else
					{
						Map_operation::paint_node(p_actual, -1);
					}
				}
				else if (selected_item->type == Item_type::Prefab)
					static_cast<Prefab_item*>(selected_item)->remove(p_actual);
			}
		}
	}

	void Builder::on_transition()
	{
		THROW_INFORMATION("Transition to gamemode Builder");
		_interacter->editor_inventory()->activate();
	}
}