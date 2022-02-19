#include "erelia.h"

Map_manager* Map_manager::_instance = nullptr;

void Map_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->set_geometry(0, _area);
	}
}

void Map_manager::_render()
{

}

void Map_manager::_change_connection_mode(Connection_mode p_mode)
{
	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		delete _widgets[i];
	}

	if (p_mode == Connection_mode::Singleplayer)
	{

	}
	else if (p_mode == Connection_mode::Multiplayer)
	{

	}
	else if (p_mode == Connection_mode::Host)
	{

	}
}

void Map_manager::_load_ui_file()
{

}

Map_manager::Map_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_load_ui_file();
	_change_connection_mode(p_mode);
}

Map_manager* Map_manager::instanciate(Connection_mode p_mode, jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Map_manager(p_mode, p_parent);
		_instance->activate();
	}
	return (_instance);
}

Map_manager* Map_manager::instance()
{
	return (_instance);
}