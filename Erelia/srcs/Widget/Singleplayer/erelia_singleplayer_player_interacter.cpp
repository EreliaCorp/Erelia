#include "erelia.h"

namespace Singleplayer
{
	void Player_interacter::_render()
	{

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
		if (Game_manager::instance()->gamemode() == Gamemode::Builder)
		{
			if (_editor_inventory->active() == false)
				_activate_editor_inventory();

			if (Console_manager::instance()->console_entry_pointed() == true || _editor_inventory->is_pointed() == true)
				return (false);

			if (jgl::Application::active_application()->mouse().get_button(jgl::Mouse_button::Left) == jgl::Input_status::Down)
			{
				jgl::Vector2Int pos = convert_screen_to_world(jgl::Application::active_application()->mouse().pos());

				Engine::instance()->map()->place_node(pos, 0, 0);
			}
		}
		else if (Game_manager::instance()->gamemode() == Gamemode::Adventure)
		{
			if (_editor_inventory->active() == true)
				_desactivate_editor_inventory();
		}

		return (false);
	}

	Player_interacter::Player_interacter(jgl::Widget* p_parent) : Graphical_widget(p_parent)
	{
		_editor_inventory = new Editor_inventory(this);
		_editor_inventory->desactivate();
	}
}
