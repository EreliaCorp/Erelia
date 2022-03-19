#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"

class Client_manager : public jgl::Widget
{
private:
	void _on_geometry_change();
	void _render();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

	Client* _client;

	Client_manager(jgl::Widget* p_parent);

	static Client_manager* _instance;

public:
	static Client_manager* instantiate(jgl::Widget* p_parent);
	static Client_manager* instance() { return (_instance); }

	Client* get_client() { return (_client); }
	static Client* client() { return (_instance->get_client()); }
};