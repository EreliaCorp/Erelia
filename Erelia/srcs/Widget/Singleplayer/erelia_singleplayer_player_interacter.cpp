#include "erelia.h"

namespace Singleplayer
{
	void Player_interacter::_render()
	{

	}

	void Player_interacter::_on_geometry_change()
	{

	}

	jgl::Bool Player_interacter::_update()
	{
		if (Game_manager::instance()->gamemode() == Gamemode::Builder)
		{
			if (Console_manager::instance()->console_entry_pointed() == true)
				return (false);

			if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down)
			{
				jgl::Vector2Int pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

				Engine::instance()->map()->place_node(pos, 0, 0);
			}
		}

		return (false);
	}

	Player_interacter::Player_interacter(jgl::Widget* p_parent) : Graphical_widget(p_parent)
	{

	}
}
