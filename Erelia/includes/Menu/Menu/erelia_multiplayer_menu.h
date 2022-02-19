#pragma once

#include "jgl.h"

#include "Menu/Submenu/erelia_server_selecter_menu.h"
#include "Menu/Submenu/erelia_server_creator_menu.h"
#include "Menu/Submenu/erelia_player_info_menu.h"

class Multiplayer_menu : public jgl::Widget
{
private:
	jgl::Button* _return_button;

	Player_info_menu* _player_info_menu;
	Server_selecter_menu* _server_selecter_menu;
	Server_creator_menu* _server_creator_menu;

	void _on_geometry_change();
	void _render();

	void _confirm_server_selection();
	void _confirm_server_creation();

public:
	Multiplayer_menu(jgl::Widget* p_parent);

	void start_server_creation();
	void start_selecter_menu();
};