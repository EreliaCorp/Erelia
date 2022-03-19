#pragma once

#include "jgl.h"

#include "Routine/erelia_battle_routine.h"

class Battle_manager : public jgl::Widget
{
private:
	static Battle_manager* _instance;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Battle_manager(jgl::Widget* p_parent = nullptr);

	void _send_command();
	void _initialize_server();
	void _initialize_client();
	void _initiate();

public:
	static Battle_manager* instanciate(jgl::Widget* p_parent = nullptr);
	static Battle_manager* instance();
};