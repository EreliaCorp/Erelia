#pragma once

#include "jgl.h"

#include "Menu/Menu/erelia_main_menu.h"

class Main_application : public jgl::Widget
{
private:
	UI_configuration_file* _configuration_file;

	Main_menu* _main_menu;

	static Main_application* _instance;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

public:
	Main_application(jgl::Widget* p_parent);
	~Main_application();
	static Main_application* instance();

	void launch_game_singleplayer(jgl::String p_world_name);
	void launch_game_multiplayer(jgl::String p_server_name, jgl::String p_server_ip, jgl::String p_player_username, jgl::String p_player_password);
	void launch_game_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password);

	void set_error_text(jgl::String p_text);
	void return_to_main_menu();
};
