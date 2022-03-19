#include "erelia.h"

Battle_manager* Battle_manager::_instance = nullptr;

void Battle_manager::_on_geometry_change()
{

}

void Battle_manager::_render()
{

}

jgl::Bool Battle_manager::_update()
{
	return (false);
}

Battle_manager::Battle_manager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

void Battle_manager::_send_command()
{

}

void Battle_manager::_initialize_server()
{

}

void Battle_manager::_initialize_client()
{

}

void Battle_manager::_initiate()
{

}

Battle_manager* Battle_manager::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Battle_manager(p_parent);
	}
	return (_instance);
}

Battle_manager* Battle_manager::instance()
{
	return (_instance);
}
