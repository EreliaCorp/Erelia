#include "widget/Screen/game_world/Widget/erelia_player_interacter_activity.h"
#include "widget/Screen/game_world/Widget/erelia_map_operation.h"
#include "widget/Commun/erelia_console_manager.h"

namespace Player_interact_activity
{
	Area_builder::Area_builder(Player_interacter* p_interacter) : Abstract_activity(p_interacter)
	{

	}

	void Area_builder::execute()
	{
		jgl::Input_status left_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left);
		jgl::Input_status right_button = jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Right);
		jgl::Input_status shift_key = jgl::Application::active_application()->keyboard().get_key(jgl::Key::Shift);

		jgl::Vector2Int p_actual, p_start, p_end;

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

				Map_operation::place_multiple_area_value(p_start, p_end, _interacter->publisher()->context()->monster_value);

			}
			else if (right_button == jgl::Input_status::Release)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				Map_operation::place_multiple_area_value(p_start, p_end, -1);
			}
		}
		else if (shift_key == jgl::Input_status::Up)
		{
			if (left_button == jgl::Input_status::Down)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
					Map_operation::place_single_area_value(p_actual, _interacter->publisher()->context()->monster_value);
				else
					Map_operation::paint_area_value(p_actual, _interacter->publisher()->context()->monster_value);
			}
			else if (right_button == jgl::Input_status::Down)
			{
				_interacter->compose_pos(p_actual, p_start, p_end);

				if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Alt) == jgl::Input_status::Up)
					Map_operation::place_single_area_value(p_actual, -1);
				else
					Map_operation::paint_area_value(p_actual, -1);
			}
		}
	}

	void Area_builder::on_transition()
	{
		THROW_INFORMATION("Transition to gamemode Area builder");
		_interacter->editor_inventory()->desactivate();
	}
}