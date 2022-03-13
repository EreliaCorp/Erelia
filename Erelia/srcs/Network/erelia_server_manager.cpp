#include "erelia.h"

Server_manager* Server_manager::_instance = nullptr;

Server_manager* Server_manager::instantiate(jgl::Widget* p_parent)
{
	_instance = new Server_manager(p_parent);
	_instance->activate();
	return (_instance);
}

Server_manager::Server_manager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_server = new Server(SERVER_PORT);
	_server->start();
}

void Server_manager::_on_geometry_change()
{

}

void Server_manager::_render()
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

void Server_manager::send_global_message(jgl::String p_text)
{
	static Message result(Server_message::Console_message);

	result.clear();

	result << p_text;

	_server->send_to_all(result);
}

void Server_manager::send_private_message(jgl::String p_text, Connection* p_client)
{
	static Message result(Server_message::Console_message);

	result.clear();

	result << p_text;

	_server->send_to(p_client, result);
}