#include "erelia.h"

void Multiplayer_menu::_on_geometry_change()
{
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 8, _area.y / 20);
	_return_button->set_geometry(jgl::Vector2Int(_area.x - button_size.x, 0), button_size);

	_server_selecter_menu->set_geometry(0, _area);
	_server_creator_menu->set_geometry(0, _area);
	_player_info_menu->set_geometry(0, _area);
}

void Multiplayer_menu::_render()
{

}

void Multiplayer_menu::_confirm_server_selection()
{
	if (_server_selecter_menu->selected_server_info().server_name != "" && _server_selecter_menu->selected_server_info().server_ip != "" &&
		_player_info_menu->username() != "" && _player_info_menu->password() != "")
	{
		Singleton_atlas::configuration_file.set_player_username(_player_info_menu->username());
		Singleton_atlas::configuration_file.set_player_password(_player_info_menu->password());
		Singleton_atlas::configuration_file.save(Path_atlas::ui_configuration_file);
		Main_application::instance()->launch_game_multiplayer(_server_selecter_menu->selected_server_info().server_name, _server_selecter_menu->selected_server_info().server_ip, _player_info_menu->username(), _player_info_menu->password());
	}
}

void Multiplayer_menu::_confirm_server_creation()
{
	if (_server_creator_menu->server_name() != "" && _server_creator_menu->server_ip() != "")
	{
		Singleton_atlas::configuration_file.add_server(
			_server_creator_menu->server_ip(),
			_server_creator_menu->server_name()
		);
		Singleton_atlas::configuration_file.set_player_username(_player_info_menu->username());
		Singleton_atlas::configuration_file.set_player_password(_player_info_menu->password());
		Singleton_atlas::configuration_file.load(Path_atlas::ui_configuration_file);
		start_selecter_menu();
	}
}

Multiplayer_menu::Multiplayer_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_return_button = new jgl::Button([&](jgl::Data_contener& p_param) {Main_application::instance()->return_to_main_menu(); }, this);
	_return_button->label().set_text("Return to menu");
	_return_button->selected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_selected_texture());
	_return_button->unselected_box().set_sprite_sheet(Texture_atlas::instance()->basic_frame_texture());
	_return_button->activate();

	_server_selecter_menu = new Server_selecter_menu(
		[&](jgl::Data_contener& p_param) {_confirm_server_selection(); }, // Loading lambda
		[&](jgl::Data_contener& p_param) {start_server_creation(); }, // Creating Lambda
		this);

	_server_creator_menu = new Server_creator_menu(
		[&](jgl::Data_contener& p_param) {_confirm_server_creation(); }, //Confirm lambda
		[&](jgl::Data_contener& p_param) {start_selecter_menu(); }, //Cancel lambda
		this);

	_player_info_menu = new Player_info_menu(this);
}

void Multiplayer_menu::start_server_creation()
{
	_server_creator_menu->start();

	_server_creator_menu->activate();

	_server_selecter_menu->desactivate();
	_player_info_menu->desactivate();
}

void Multiplayer_menu::start_selecter_menu()
{
	_server_selecter_menu->start();
	_player_info_menu->start();

	_server_selecter_menu->activate();
	_player_info_menu->activate();

	_server_creator_menu->desactivate();
}