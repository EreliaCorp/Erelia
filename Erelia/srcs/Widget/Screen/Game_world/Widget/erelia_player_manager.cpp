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
		if (Engine::instance()->player()->is_flying() == true)
		{
			tmp_entity->move(delta);
		}
		else
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
				_handle_player_encounter(p_client, tmp_entity->destination());
			}
		}
	}
}

void Player_manager::_handle_player_encounter(Connection* p_client, jgl::Vector2Int p_pos)
{
	jgl::Int tmp_value = Engine::instance()->map()->encounter(p_pos);

	if (tmp_value != -1 && tmp_value < Engine::instance()->encounter_areas().size())
	{
		jgl::cout << "There is a encounter area !" << jgl::endl;
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
