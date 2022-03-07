#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"

class Client_manager : public jgl::Widget
{
private:
	jgl::Size_t _ping;

	void _on_geometry_change();
	void _render();
	jgl::Bool _update();
	jgl::Bool _fixed_update();

	Client* _client;

	Client_manager(jgl::Widget* p_parent);

	static Client_manager* _instance;

public:
	void send_ping_request();
	void set_ping(jgl::Size_t p_ping) { _ping = p_ping; }

	static Client_manager* instantiate(jgl::Widget* p_parent);
	static Client_manager* instance() { return (_instance); }

	Client* get_client() { return (_client); }
	static Client* client() { return (_instance->get_client()); }
};