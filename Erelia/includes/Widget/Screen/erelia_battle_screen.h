#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_abstract_screen.h"

#include "Routine/erelia_battle_routine.h"

#include "widget/Manager/erelia_battle_manager.h"

class Battle_screen : public Abstract_screen
{
private:
	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Battle_screen(jgl::Widget* p_parent);

	void _initialize_server();
	void _initialize_client();

	static Battle_screen* _instance;

public:
	void start();

	static Battle_screen* instanciate(jgl::Widget* p_parent);
	static Battle_screen* instance() { return (_instance); }
};