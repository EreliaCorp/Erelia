#include "erelia.h"

void Player_controller::_on_geometry_change()
{

}

void Player_controller::_render()
{

}

void Player_controller::_send_motion_command(jgl::Vector2Int p_delta)
{
	static Message msg(Server_message::Player_movement);

	msg.clear();

	msg << Engine::instance()->player()->id();
	msg << p_delta;

	Client_manager::client()->send(msg);
}

jgl::Bool Player_controller::_update()
{
	if (Engine::instance()->player() == nullptr || Console_manager::instance()->console_active() == true)
		return false;

	jgl::Key keys[4] = { jgl::Key::Z, jgl::Key::Q, jgl::Key::S, jgl::Key::D};
	jgl::Vector2Int delta_value[4] = { jgl::Vector2(0, -1) , jgl::Vector2(-1, 0) , jgl::Vector2(0, 1) , jgl::Vector2(1, 0) };
	jgl::Vector2Int delta_pos = 0;

	for (jgl::Size_t i = 0; i < 4; i++)
		if (jgl::Application::active_application()->keyboard().get_key(keys[i]) == jgl::Input_status::Down)
			delta_pos += delta_value[i];

	if (delta_pos != 0 && Engine::instance()->player()->is_moving() == false && Console_manager::instance()->console_active() == false)
	{
		_send_motion_command(delta_pos);
	}

	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_1) == jgl::Input_status::Release)
	{
		Engine::instance()->map()->set_node_size(8);
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_2) == jgl::Input_status::Release)
	{
		Engine::instance()->map()->set_node_size(16);
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_3) == jgl::Input_status::Release)
	{
		Engine::instance()->map()->set_node_size(32);
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_4) == jgl::Input_status::Release)
	{
		Engine::instance()->map()->set_node_size(64);
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Key_9) == jgl::Input_status::Release)
	{
		Engine::instance()->map()->set_node_size(2);
	}

	return (false);
}

Player_controller::Player_controller(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

}