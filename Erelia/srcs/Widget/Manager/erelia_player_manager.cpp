#include "erelia.h"

Player_manager* Player_manager::_instance = nullptr;

void Player_manager::_on_geometry_change()
{
	_player_controller->set_geometry(0, _area);
	_player_interacter->set_geometry(0, _area);
}

void Player_manager::_render()
{
	
}

jgl::Bool Player_manager::_update()
{
	return (false);
}


void Player_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Player_movement, SERVER_ACTIVITY{
			Routine::treat_player_motion(p_client, p_msg);
		});
}

void Player_manager::_initialize_client()
{

}

void Player_manager::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Player_manager::Player_manager(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{
	_player_controller = new Player_controller(this);
	_player_controller->activate();

	_player_interacter = new Player_interacter(this);
	_player_interacter->activate();

	_initiate();
}

Player_manager* Player_manager::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Player_manager(p_parent);
		_instance->activate();
	}
	return (_instance);
}

Player_manager* Player_manager::instance()
{
	return (_instance);
}