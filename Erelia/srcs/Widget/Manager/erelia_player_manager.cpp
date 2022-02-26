#include "erelia.h"

Player_manager* Player_manager::_instance = nullptr;

void Player_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->set_geometry(0, _area);
	}
}

void Player_manager::_render()
{

}

void Player_manager::_change_connection_mode(Connection_mode p_mode)
{
	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		delete _widgets[i];
	}
	
	Player* player = new Player();

	if (p_mode == Connection_mode::Singleplayer)
	{
		_widgets.push_back(new Singleplayer::Player_updater(this));

		player->set_id(0);
	}
	else if (p_mode == Connection_mode::Multiplayer)
	{

	}
	else if (p_mode == Connection_mode::Host)
	{

	}

	Engine::instance()->initialize_player(player);

	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->activate();
	}
}

void Player_manager::_load_ui_file()
{

}

Player_manager::Player_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_mode = Gamemode::Adventure;

	_load_ui_file();
	_change_connection_mode(p_mode);
}

Player_manager* Player_manager::instanciate(Connection_mode p_mode, jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Player_manager(p_mode, p_parent);
		_instance->activate();
	}
	return (_instance);
}

Player_manager* Player_manager::instance()
{
	return (_instance);
}