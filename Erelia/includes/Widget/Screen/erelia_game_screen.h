#pragma once

#include "Enum/erelia_enum.h"

#include "Routine/erelia_client_routine.h"

#include "Structure/Data/Engine/erelia_engine.h"

#include "Widget/Manager/erelia_map_manager.h"
#include "Widget/Manager/erelia_player_manager.h"
#include "Widget/Manager/erelia_entity_manager.h"
#include "Widget/Manager/erelia_console_manager.h"

class Game_screen : public Abstract_screen
{
protected:
	Gamemode _gamemode;

	Game_screen(jgl::Widget* p_parent);

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

	void _initialize_server();
	void _initialize_client();

	static Game_screen* _instance;

public:
	void start();

	Gamemode gamemode() { return (_gamemode); }
	void set_gamemode(Gamemode p_gamemode) { _gamemode = p_gamemode; }

	static Game_screen* instanciate(jgl::Widget* p_parent);
	static Game_screen* instance() { return (_instance); }
};