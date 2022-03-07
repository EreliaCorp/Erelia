#include "erelia.h"

Abstract_screen::Abstract_screen(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

void Abstract_screen::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}