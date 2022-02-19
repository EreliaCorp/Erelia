#include "erelia.h"


Entity_manager* Entity_manager::_instance = nullptr;

void Entity_manager::_on_geometry_change()
{
	for (jgl::Size_t i = 0; i < _widgets.size(); i++)
	{
		_widgets[i]->set_geometry(0, _area);
	}
}

void Entity_manager::_render()
{

}

void Entity_manager::_change_connection_mode(Connection_mode p_mode)
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

void Entity_manager::_load_ui_file()
{

}

Entity_manager::Entity_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_load_ui_file();
	_change_connection_mode(p_mode);
}

Entity_manager* Entity_manager::instanciate(Connection_mode p_mode, jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Entity_manager(p_mode, p_parent);
		_instance->activate();
	}
	return (_instance);
}
	
Entity_manager* Entity_manager::instance()
{
	return (_instance);
}