#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"

class Server_manager : public jgl::Updater_widget
{
private:
	void _on_geometry_change();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

	Server* _server;

	Server_manager(jgl::Widget* p_parent);

	static Server_manager* _instance;

public:
	static Server_manager* instantiate(jgl::Widget* p_parent);
	static Server_manager* instance() { return (_instance); }

	Server* get_server() { return (_server); }
	static Server* server() { return (_instance->get_server()); }
};