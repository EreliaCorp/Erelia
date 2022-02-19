#pragma once

#include "jgl.h"

class Server_creator_menu : public jgl::Widget
{
private:
	jgl::Text_label* _server_name_label;
	jgl::Text_entry* _server_name_entry;

	jgl::Text_label* _server_ip_label;
	jgl::Text_entry* _server_ip_entry;

	jgl::Button* _confirm_server_creation_button;
	jgl::Button* _cancel_server_creation_button;

	void _on_geometry_change();
	void _render();

public:
	Server_creator_menu(std::function< void(jgl::Data_contener&) > p_funct_confirm, std::function< void(jgl::Data_contener&) > p_funct_cancel, jgl::Widget* p_parent);

	void start();

	jgl::String server_name() { return (_server_name_entry->label().text()); }
	jgl::String server_ip() { return (_server_ip_entry->label().text()); }
};