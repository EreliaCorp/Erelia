#include "erelia.h"

void Game_battle_screen::_on_geometry_change()
{
	button->set_geometry(100, jgl::Vector2Int(150, 50));
}

Game_battle_screen::Game_battle_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	button = new jgl::Button([&](jgl::Data_contener& p_param) {
		jgl::cout << "Battle screen button" << jgl::endl;
		Publisher::instance()->notify(Main_application::Event::Go_world);
		}, this);
	button->label().set_text("Go world");
	button->activate();
}

void Game_battle_screen::focus()
{

}

void Game_battle_screen::unfocus()
{

} 