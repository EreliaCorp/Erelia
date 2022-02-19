#include "erelia.h"

void Singleplayer_menu::_on_geometry_change()
{
	jgl::Vector2Int button_size = jgl::Vector2Int(_area.x / 8, _area.y / 20);
	_return_button->set_geometry(jgl::Vector2Int(_area.x - button_size.x, 0), button_size);

	_selecter_menu->set_geometry(0, _area);
	_world_creator_menu->set_geometry(0, _area);
}

void Singleplayer_menu::_render()
{

}

void Singleplayer_menu::_confirm_world_selection()
{
	if (_selecter_menu->selected_world() != "")
		Main_application::instance()->launch_game_singleplayer(_selecter_menu->selected_world());
}

void Singleplayer_menu::_confirm_world_creation()
{
	jgl::String name = _world_creator_menu->world_name();
	jgl::Int i = 1;

	while (jgl::check_file_exist(Path_atlas::world_path + name) == true)
	{
		name = _world_creator_menu->world_name() + " (" + jgl::itoa(i) + ")";
		i++;
	}

	Path_atlas::compose_world_folder(name);
	Main_application::instance()->launch_game_singleplayer(name);
}


Singleplayer_menu::Singleplayer_menu(jgl::Widget* p_parent) : jgl::Widget(p_parent)
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
}

void Singleplayer_menu::start_world_creation()
{
	_world_creator_menu->start();

	_world_creator_menu->activate();

	_selecter_menu->desactivate();
}

void Singleplayer_menu::start_selecter_menu()
{
	_selecter_menu->start();

	_selecter_menu->activate();

	_world_creator_menu->desactivate();
}