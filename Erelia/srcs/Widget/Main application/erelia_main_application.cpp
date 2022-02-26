#include "erelia.h"

Main_application* Main_application::_instance = nullptr;


void Main_application::_on_geometry_change()
{
	_main_menu->set_geometry(0, _area);
}

void Main_application::_render()
{

}

jgl::Bool Main_application::_update()
{
	if (Singleton_atlas::client() != nullptr && Singleton_atlas::client()->is_connected() == true)
		Singleton_atlas::client()->update();
	if (Singleton_atlas::server() != nullptr)
		Singleton_atlas::server()->update();

	return(false);
}

jgl::Bool Main_application::_fixed_update()
{
	return(false);
}

void Main_application::launch_game_singleplayer(jgl::String p_world_name)
{
	Game_manager::instanciate_singleplayer(p_world_name, this);

	if (Game_manager::instance()->loading_status() == Game_manager::Loading_status::Connection_complete)
	{
		_main_menu->desactivate();
		Game_manager::instance()->activate();
	}
	else
	{
		return_to_main_menu();
	}
}

void Main_application::launch_game_multiplayer(jgl::String p_server_name, jgl::String p_server_ip, jgl::String p_player_username, jgl::String p_player_password)
{
	Game_manager::instanciate_multiplayer(p_server_ip, p_player_username, p_player_password, this);

	if (Game_manager::instance()->loading_status() == Game_manager::Loading_status::Connection_complete)
	{
		_main_menu->desactivate();
		Game_manager::instance()->activate();
	}
	else if (Game_manager::instance()->loading_status() == Game_manager::Loading_status::Timeout_multiplayer_connection)
	{
		return_to_main_menu();
		_main_menu->set_error_text("Error while connecting to server : timeout");
	}
}

void Main_application::launch_game_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password)
{
	Game_manager::instanciate_host(p_world_name, p_player_username, p_player_password, this);

	if (Game_manager::instance()->loading_status() == Game_manager::Loading_status::Connection_complete)
	{
		_main_menu->desactivate();
		Game_manager::instance()->activate();
	}
	else
	{
		return_to_main_menu();
		_main_menu->set_error_text("Can't host a game");
	}
}

Main_application::Main_application(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	Path_atlas::compose_ressource_folder();

	Texture_atlas::instanciate();
	Texture_atlas::instance()->add_texture("Basic_frame", new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_path, 3));
	Texture_atlas::instance()->add_texture("Basic_frame_selected", new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_pressed_path, 3));
	Texture_atlas::instance()->add_texture("chunk_sprite_sheet", new jgl::Sprite_sheet(Path_atlas::chunk_sprite_sheet_path, jgl::Vector2Int(32, 66)));

	_instance = this;
	if (jgl::check_file_exist(Path_atlas::ui_configuration_path + Path_atlas::ui_configuration_file) == false)
	{
		Singleton_atlas::configuration_file.save(Path_atlas::ui_configuration_file);
	}
	Singleton_atlas::configuration_file.load(Path_atlas::ui_configuration_file);

	_main_menu = new Main_menu(this);

	_main_menu->activate();
}
Main_application::~Main_application()
{
	if (Game_manager::instance() != nullptr)
		delete Game_manager::instance();
}

Main_application* Main_application::instance()
{
	return (_instance);
}

void Main_application::set_error_text(jgl::String p_text)
{
	_main_menu->set_error_text(p_text);
}

void Main_application::return_to_main_menu()
{
	_main_menu->set_error_text("");
	_main_menu->activate();
	_main_menu->start();
}