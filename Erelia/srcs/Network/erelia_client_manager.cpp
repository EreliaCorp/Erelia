#include "Network/erelia_client_manager.h"
#include "structure/File/erelia_UI_configuration_file.h"

Client_manager* Client_manager::_instance = nullptr;

Client_manager* Client_manager::instantiate(jgl::Widget* p_parent)
{
	_instance = new Client_manager(p_parent);
	_instance->activate();
	return (_instance);
}

Client_manager::Client_manager(jgl::Widget* p_parent) : jgl::Updater_widget(p_parent)
{
	_client = new Client();
	_client->connect(UI_configuration_file::server_address(), SERVER_PORT);
}

void Client_manager::_on_geometry_change()
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