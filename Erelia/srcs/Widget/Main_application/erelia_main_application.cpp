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

	_initiate();
}

Main_application::~Main_application()
{ 
	UI_configuration_file::save(Path_atlas::ui_config_path);
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

}

void Main_application::_render()
{

}

void Main_application::_start_server()
{
	Server_manager::instantiate(this);
}

void Main_application::_start_client()
{
	Client_manager::instantiate(this);
}

void Main_application::_initialize_client()
{

}

void Main_application::_initialize_server()
{

}

jgl::Bool Main_application::_update()
{
	return (false);
}

void Main_application::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}
