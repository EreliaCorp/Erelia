#include "erelia.h"

void Game_world_screen::_on_geometry_change()
{

}

Game_world_screen::Game_world_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	State_machine::instanciate();
	Publisher::instanciate();
}

void Game_world_screen::focus()
{

}

void Game_world_screen::unfocus()
{

}