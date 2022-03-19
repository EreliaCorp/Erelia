#include "erelia.h"

Client_manager* Client_manager::_instance = nullptr;

Client_manager* Client_manager::instantiate(jgl::Widget* p_parent)
{
	_instance = new Client_manager(p_parent);
	_instance->activate();
	return (_instance);
}

void Client_manager::_on_geometry_change()
{

}

void Client_manager::_render()
{

}

jgl::Bool Client_manager::_update()
{
	_client->update();
	return(false);
}

jgl::Bool Client_manager::_fixed_update()
{
	return(false);
}

Client_manager::Client_manager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_client = new Client();
	_client->connect(UI_configuration_file::server_address(), SERVER_PORT);
}