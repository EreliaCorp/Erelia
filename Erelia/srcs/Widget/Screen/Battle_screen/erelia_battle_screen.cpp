#include "erelia.h"

Battle_screen* Battle_screen::_instance = nullptr;

void Battle_screen::_on_geometry_change()
{
	
}

void Battle_screen::_render()
{
	
}

jgl::Bool Battle_screen::_update()
{
	return (false);
}

Battle_screen::Battle_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	
}

void Battle_screen::_initialize_server()
{
	
}

void Battle_screen::_initialize_client()
{
	
}

void Battle_screen::start()
{
	
}

Battle_screen* Battle_screen::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Battle_screen(p_parent);
		_instance->activate();
	}
	return (_instance);
}