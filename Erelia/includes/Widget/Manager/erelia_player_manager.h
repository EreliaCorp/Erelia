#pragma once

#include "jgl.h"

#include "Routine/erelia_entity_routine.h"

#include "Widget/Commun/erelia_graphical_widget.h"
#include "Widget/Commun/erelia_player_controller.h"
#include "Widget/Commun/erelia_player_interacter.h"

class Player_manager : public Graphical_widget
{
private:
	Player_controller* _player_controller;
	Player_interacter* _player_interacter;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	void _initialize_server();
	void _initialize_client();
	void _initiate();

	Player_manager(jgl::Widget* p_parent = nullptr);

	static Player_manager* _instance;
public:
	static Player_manager* instanciate(jgl::Widget* p_parent = nullptr);
	static Player_manager* instance();
};