#include "erelia.h"

void Game_world_screen::_on_geometry_change()
{
	button->set_geometry(100, jgl::Vector2Int(150, 50));
}

Game_world_screen::Game_world_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	button = new jgl::Button([&](jgl::Data_contener& p_param) {
		Publisher::instance()->notify(Main_application::Event::Go_battle);
		}, this);
	button->label().set_text("Go battle");
	button->activate();
}

void Game_world_screen::focus()
{

}

void Game_world_screen::unfocus()
{

}