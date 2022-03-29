#include "widget/Screen/Game_world/Widget/erelia_player_manager.h"
#include "structure/Data/Engine/erelia_engine.h"
#include "widget/Commun/erelia_console_manager.h"

void Player_manager::_on_geometry_change()
{

}

void Player_manager::_send_motion_command(jgl::Vector2Int p_delta)
{
	static Message msg(Server_message::Player_movement);

	msg.clear();

	msg << Engine::instance()->player()->id();
	msg << p_delta;

	Client_manager::client()->send(msg);
}

void Player_manager::_treat_player_motion(Connection* p_client, Message& p_msg)
{
	jgl::Long id;
	jgl::Vector2Int delta;

	p_msg >> id;
	p_msg >> delta;

	Entity* tmp_entity = Engine::instance()->entity(id);

	if (tmp_entity != nullptr && tmp_entity->is_moving() == false)
	{
		jgl::Vector2Int result = 0;

		jgl::Vector2Int delta_value[2] = { jgl::Vector2Int(1, 0), jgl::Vector2Int(0, 1) };

		for (jgl::Size_t i = 0; i < 2; i++)
		{
			if (Engine::instance()->player()->is_flying() == true || Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), delta * delta_value[i]) == true)
			{
				result += delta * delta_value[i];
			}
		}

		if (result != delta || Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), delta) == true)
		{
			tmp_entity->move(result);
		}
	}
}

jgl::Bool Player_manager::_update()
{
	if (Engine::instance() == nullptr || Engine::instance()->player() == nullptr || Console_manager::instance()->console_active() == true)
		return false;

	jgl::Key keys[4] = { jgl::Key::Z, jgl::Key::Q, jgl::Key::S, jgl::Key::D };
	jgl::Vector2Int delta_value[4] = { jgl::Vector2(0, -1) , jgl::Vector2(-1, 0) , jgl::Vector2(0, 1) , jgl::Vector2(1, 0) };
	jgl::Vector2Int delta_pos = 0;

	for (jgl::Size_t i = 0; i < 4; i++)
		if (jgl::Application::active_application()->keyboard().get_key(keys[i]) == jgl::Input_status::Down)
			delta_pos += delta_value[i];

	if (delta_pos != 0 && Engine::instance()->player()->is_moving() == false)
	{
		_send_motion_command(delta_pos);
	}
	return (false);
}

void Player_manager::_initialize_client()
{

}

void Player_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Player_movement, SERVER_ACTIVITY{
			_treat_player_motion(p_client, p_msg);
		});
}

Player_manager::Player_manager(jgl::Widget* p_parent) : jgl::Updater_widget(p_parent)
{
	_initiate();
}
