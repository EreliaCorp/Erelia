#pragma once

#include "jgl.h"

#include "Menu/Menu/erelia_singleplayer_menu.h"
#include "Menu/Menu/erelia_multiplayer_menu.h"
#include "Menu/Menu/erelia_host_menu.h"

class Main_menu : public jgl::Widget
{
private:
	Singleplayer_menu* _singleplayer_menu;
	jgl::Button* _singleplayer_button;

	Multiplayer_menu* _multiplayer_menu;
	jgl::Button* _multiplayer_button;

	Host_menu* _host_menu;
	jgl::Button* _host_button;

	jgl::Button* _setting_button;
	jgl::Button* _quit_button;

	jgl::Text_label* _error_label;

	void _activate_main_menu();
	void _activate_menu(jgl::Widget* p_menu);
	void _on_geometry_change();

	void _calc_text_size();
	void _render();

public:
	Main_menu(jgl::Widget* p_parent);

	void activate_singleplayer_menu();
	void activate_multiplayer_menu();
	void activate_host_menu();
	void set_error_text(jgl::String p_text);
	void start();
};