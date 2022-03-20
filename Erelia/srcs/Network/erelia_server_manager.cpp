#include "Network/erelia_server_manager.h"

Server_manager* Server_manager::_instance = nullptr;

Server_manager* Server_manager::instantiate(jgl::Widget* p_parent)
{
	_instance = new Server_manager(p_parent);
	_instance->activate();
	return (_instance);
}

Server_manager::Server_manager(jgl::Widget* p_parent) : jgl::Updater_widget(p_parent)
{
	_server = new Server(SERVER_PORT);
	_server->start();
}

void Server_manager::_on_geometry_change()
{

}

jgl::Bool Server_manager::_update()
{
	_server->update();
	return(false);
}

jgl::Bool Server_manager::_fixed_update()
{
	return(false);
}