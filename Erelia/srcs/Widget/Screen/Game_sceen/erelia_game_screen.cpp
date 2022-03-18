#include "erelia.h"

Game_screen* Game_screen::_instance = nullptr;

Game_screen::Game_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	_gamemode = Gamemode::Area_builder;

	Engine::instanciate();
	Map_manager::instanciate(this);
	Player_manager::instanciate(this);
	Entity_manager::instanciate(this);
	Console_manager::instanciate(this);

	_initiate();
}

void Game_screen::_on_geometry_change()
{
	Engine::instance()->map()->unbake();
	Map_manager::instance()->set_geometry(0, _area);
	Player_manager::instance()->set_geometry(0, _area);
	Entity_manager::instance()->set_geometry(0, _area);
	Console_manager::instance()->set_geometry(0, _area);
}

void Game_screen::_render()
{
	
}

jgl::Bool Game_screen::_update()
{

	return(false);
}

jgl::Bool Game_screen::_fixed_update()
{
	return (false);
}

void Game_screen::_initialize_server()
{
	
}

void Game_screen::_initialize_client()
{

	Client_manager::client()->add_activity(Server_message::Gamemode_message, CLIENT_ACTIVITY{
			Routine::receive_gamemode_change(p_msg);
		});
}

void Game_screen::start()
{
		
}

Game_screen* Game_screen::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Game_screen(p_parent);
		_instance->activate();
	}
	return (_instance);
}