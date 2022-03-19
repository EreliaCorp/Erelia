#pragma once

#include "jgl.h"

#include "Routine/erelia_battle_routine.h"

#include "Structure/Atlas/erelia_battle_room_atlas.h"

class Battle_manager : public jgl::Widget
{
private:
	static Battle_manager* _instance;

	Battle_room* _active_battle_room;

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

	Battle_room* generate_battle_room(Encounter_area* p_encounter_area);
	void set_battle_room(Battle_room* p_battle_room);

	static void start_battle_room(Battle_room* p_battle_room);
};