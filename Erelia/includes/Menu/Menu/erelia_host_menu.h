#pragma once

#include "jgl.h"

#include "Menu/Submenu/erelia_world_selecter_menu.h"
#include "Menu/Submenu/erelia_world_creator_menu.h"
#include "Menu/Submenu/erelia_player_info_menu.h"

class Host_menu : public jgl::Widget
{
private:
	jgl::Button* _return_button;

	Player_info_menu* _player_info_menu;
	World_selecter_menu* _selecter_menu;
	World_creator_menu* _world_creator_menu;

	void _on_geometry_change();
	void _render();

	void _launch_world(jgl::String p_path);
	void _confirm_world_selection();
	void _confirm_world_creation();

public:
	Host_menu(jgl::Widget* p_parent);
	void start_selecter_menu();
	void start_world_creation();
};