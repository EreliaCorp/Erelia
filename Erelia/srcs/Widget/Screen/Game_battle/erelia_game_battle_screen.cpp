#include "erelia.h"

void Game_battle_screen::_on_geometry_change()
{

}

Game_battle_screen::Game_battle_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent),
	_context(nullptr)
{
	State_machine::instanciate();
	Publisher::instanciate();

	_context = Publisher::instance()->context();
}

void Game_battle_screen::focus()
{
	THROW_INFORMATION("Focus on game battle screen");
}

void Game_battle_screen::unfocus()
{
	THROW_INFORMATION("Unfocus on game battle screen");
} 