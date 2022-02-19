#pragma once

#include "jgl.h"

class Server_selecter_menu : public jgl::Widget
{
private:
	jgl::Size_t _server_list_start;

	jgl::Button* _up_slider_button;
	jgl::Array<jgl::Button*> _server_loader_button_array;
	jgl::Button* _down_slider_button;
	jgl::Button* _new_server_button;

	void _load_server_list();

	void _on_geometry_change();
	void _render();

public:
	Server_selecter_menu(std::function< void(jgl::Data_contener&) > p_funct_load, std::function< void(jgl::Data_contener&) > p_funct_create, jgl::Widget* p_parent);
	UI_configuration_file::Server_info selected_server_info();
	void start();
};