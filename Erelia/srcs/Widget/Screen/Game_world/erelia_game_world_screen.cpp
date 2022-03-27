#include "Widget/Screen/Game_world/erelia_game_world_screen.h"

void Game_world_screen::_on_geometry_change()
{
	_map_renderer->set_geometry(0, _area);
	_map_manager->set_geometry(0, _area);
}

Game_world_screen::Game_world_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	State_machine::instanciate();
	Publisher::instanciate();

	_map_renderer = new Map_renderer(this);
	_map_manager = new Map_manager(this);
}

void Game_world_screen::focus()
{
	THROW_INFORMATION("Focus on game world screen");
	_map_renderer->activate();
	_map_manager->activate();
}

void Game_world_screen::unfocus()
{
	THROW_INFORMATION("Unfocus on game world screen");
	_map_renderer->desactivate();
	_map_manager->desactivate();
}