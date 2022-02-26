#include "erelia.h"

namespace Singleplayer
{
	void Player_updater::_on_geometry_change()
	{

	}

	void Player_updater::_render()
	{

	}

	jgl::Bool Player_updater::_update()
	{
		if (Engine::instance()->player() == nullptr || Console_manager::instance()->console_active() == true)
			return false;

		jgl::Key keys[4] = { jgl::Key::Z, jgl::Key::Q, jgl::Key::S, jgl::Key::D};
		jgl::Vector2Int delta_value[4] = { jgl::Vector2(0, -1) , jgl::Vector2(-1, 0) , jgl::Vector2(0, 1) , jgl::Vector2(1, 0) };
		jgl::Vector2Int delta_pos = 0;

		for (jgl::Size_t i = 0; i < 4; i++)
			if (jgl::Application::active_application()->keyboard().get_key(keys[i]) == jgl::Input_status::Down)
				delta_pos += delta_value[i];
		 
		if (delta_pos != 0 && Engine::instance()->player()->is_moving() == false)
		{
			Engine::instance()->player()->move(delta_pos);
			return (true);
		}


		Engine::instance()->player()->update();

		return (false);
	}

	Player_updater::Player_updater(jgl::Widget* p_parent) : Graphical_widget(p_parent)
	{

	}
}