#include "erelia.h"

Main_application* Main_application::_instance = nullptr;

Main_application::Main_application(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	UI_configuration_file::load(Path_atlas::ui_config_path);
	Translation_atlas::load(UI_configuration_file::language());

	Texture_atlas::instanciate();
	Texture_atlas::instance()->add_texture(Path_atlas::basic_frame_texture_name, new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_path, 3));
	Texture_atlas::instance()->add_texture(Path_atlas::basic_frame_texture_pressed_name, new jgl::Sprite_sheet(Path_atlas::basic_frame_texture_pressed_path, 3));
	Texture_atlas::instance()->add_texture(Path_atlas::chunk_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::chunk_sprite_sheet_path, jgl::Vector2Int(32, 66)));
	Texture_atlas::instance()->add_texture(Path_atlas::prefab_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::prefab_sprite_sheet_path, jgl::Vector2Int(8, 44)));
	Texture_atlas::instance()->add_texture(Path_atlas::UI_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::UI_sprite_sheet_path, jgl::Vector2Int(10, 10)));
	Texture_atlas::instance()->add_texture(Path_atlas::monster_area_sprite_sheet_name, new jgl::Sprite_sheet(Path_atlas::monster_area_sprite_sheet_path, jgl::Vector2Int(16, 12)));

	if (UI_configuration_file::server_mode() == true)
		_start_server();

	_start_client();

	Connection_screen::instanciate(this);
	Loading_screen::instanciate(this);
	Game_screen::instanciate(this);
	Debug_screen::instanciate(this);
	Debug_screen::instance()->set_depth(1000);

	_initiate();

	transition_to_connection();
}

Main_application::~Main_application()
{ 
	UI_configuration_file::save(Path_atlas::ui_config_path);
	if (Account_atlas::instance() != nullptr)
		Account_atlas::instance()->save();
}

Main_application* Main_application::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Main_application(p_parent);
	}
	return (_instance);
}

void Main_application::_on_geometry_change()
{
	Connection_screen::instance()->set_geometry(0, _area);
	Loading_screen::instance()->set_geometry(0, _area);
	Game_screen::instance()->set_geometry(0, _area);
	Debug_screen::instance()->set_geometry(0, _area);
}

void Main_application::_render()
{

}

void Main_application::_start_server()
{
	Server_manager::instantiate(this);
	Account_atlas::instanciate();
	Account_atlas::instance()->load();
}

void Main_application::_start_client()
{
	Client_manager::instantiate(this);
}

void Main_application::transition_to_loading()
{
	Connection_screen::instance()->desactivate();
	Loading_screen::instance()->activate();
	Game_screen::instance()->desactivate();

	Loading_screen::instance()->start();
}

void Main_application::transition_to_game()
{
	Connection_screen::instance()->desactivate();
	Loading_screen::instance()->desactivate();
	Game_screen::instance()->activate();

	Game_screen::instance()->start();
}

void Main_application::transition_to_connection()
{
	Connection_screen::instance()->activate();
	Loading_screen::instance()->desactivate();
	Game_screen::instance()->desactivate();

	Connection_screen::instance()->start();
}


void Main_application::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Connection_accepted, CLIENT_ACTIVITY{
			transition_to_loading();
		});
}

void Main_application::_initialize_server()
{
	Engine::instance()->map()->load(Path_atlas::world_path);

	Server_manager::server()->set_logout_function([&](Connection* p_client, jgl::Data_contener& p_param) {
		Routine::client_logout_routine(p_client);
		});
}

jgl::Bool Main_application::_update()
{
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::F3) == jgl::Input_status::Release)
	{
		Debug_screen::instance()->set_active(!(Debug_screen::instance()->active()));
	}
	return (false);
}

void Main_application::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}
