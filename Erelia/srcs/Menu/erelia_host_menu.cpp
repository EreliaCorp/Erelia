#include "erelia.h"

void Host_menu::_on_geometry_change()
{
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 8, _area.y / 20);
	_return_button->set_geometry(jgl::Vector2Int(_area.x - button_size.x, 0), button_size);

	_selecter_menu->set_geometry(0, _area);
	_world_creator_menu->set_geometry(0, _area);
	_player_info_menu->set_geometry(0, _area);
}

void Host_menu::_render()
{

}

void Host_menu::_confirm_world_selection()
{
	if (_selecter_menu->selected_world() != "" &&
		_player_info_menu->username() != "" && _player_info_menu->password() != "")
	{
		Singleton_atlas::configuration_file.set_player_username(_player_info_menu->username());
		Singleton_atlas::configuration_file.set_player_password(_player_info_menu->password());
		Singleton_atlas::configuration_file.save(Path_atlas::ui_configuration_file);
		Main_application::instance()->launch_game_host(_selecter_menu->selected_world(), _player_info_menu->username(), _player_info_menu->password());
	}
}

void Host_menu::_confirm_world_creation()
{
	if (_world_creator_menu->world_name() != "" &&
		_player_info_menu->username() != "" && _player_info_menu->password() != "")
	{
		jgl::String name = _world_creator_menu->world_name();
		jgl::Int i = 1;

		while (jgl::check_file_exist(Path_atlas::world_path + name) == true)
		{
			name = _world_creator_menu->world_name() + " (" + jgl::itoa(i) + ")";
			i++;
		}

		Singleton_atlas::configuration_file.set_player_username(_player_info_menu->username());
		Singleton_atlas::configuration_file.set_player_password(_player_info_menu->password());
		Singleton_atlas::configuration_file.save(Path_atlas::ui_configuration_path);
		Path_atlas::compose_world_folder(name);
		Main_application::instance()->launch_game_host(name, _player_info_menu->username(), _player_info_menu->password());
	}
}


Host_menu::Host_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_return_button = new jgl::Button([&](jgl::Data_contener& p_param) {Main_application::instance()->return_to_main_menu(); }, this);
	_return_button->label().set_text("Return to menu");
	_return_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_return_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_return_button->activate();

	_selecter_menu = new World_selecter_menu(
		[&](jgl::Data_contener& p_param) {_confirm_world_selection(); }, // Loading lambda
		[&](jgl::Data_contener& p_param) {start_world_creation(); }, // Creating Lambda
		this);

	_world_creator_menu = new World_creator_menu(
		[&](jgl::Data_contener& p_param) {_confirm_world_creation(); }, //Confirm lambda
		[&](jgl::Data_contener& p_param) {start_selecter_menu(); }, //Cancel lambda
		this);

	_player_info_menu = new Player_info_menu(this);
}

void Host_menu::start_world_creation()
{
	_world_creator_menu->start();

	_world_creator_menu->activate();

	_selecter_menu->desactivate();
	_player_info_menu->desactivate();
}

void Host_menu::start_selecter_menu()
{
	_selecter_menu->start();
	_player_info_menu->start();

	_player_info_menu->activate();
	_selecter_menu->activate();

	_world_creator_menu->desactivate();
}