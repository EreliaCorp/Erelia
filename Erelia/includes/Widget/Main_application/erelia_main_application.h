#pragma once

#include "jgl.h"

#include "structure/atlas/erelia_account_atlas.h"

#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

#include "Widget/Screen/erelia_connection_screen.h"
#include "Widget/Screen/erelia_loading_screen.h"
#include "Widget/Screen/erelia_game_screen.h"
#include "Widget/Screen/erelia_battle_screen.h"

#include "Routine/erelia_client_routine.h"

#include "erelia_main_application_debug_screen.h"

class Main_application : public jgl::Widget
{
private:
	Debug_screen* _debug_screen;

	void _on_geometry_change();
	void _render();

	void _start_server();
	void _start_client();

	void _initialize_client();
	void _initialize_server();

	void _initiate();

	jgl::Bool _update();

	Main_application(jgl::Widget* p_parent = nullptr);

	static Main_application* _instance;
public:

	static Main_application* instanciate(jgl::Widget* p_parent);
	static Main_application* instance() { return (_instance); }

	~Main_application();

	void transition_to_loading();
	void transition_to_game();
	void transition_to_connection();
	void transition_to_battle();
};