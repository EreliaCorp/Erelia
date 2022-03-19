#pragma once

#include "structure/Data/Battle/erelia_battle_room.h"

class Battle_room_atlas
{
private:
	jgl::Map<jgl::Long, Battle_room*> _battle_rooms;

	Battle_room_atlas();

	static Battle_room_atlas* _instance;
public:
	jgl::Long request_new_battle_room_id();
	Battle_room* instanciate_new_room();
	void add_room(jgl::Long p_id, Battle_room* p_room);
	Battle_room* battle_room(jgl::Long p_id);

	static Battle_room_atlas* instanciate();
	static Battle_room_atlas* instance() { return (_instance); }
};