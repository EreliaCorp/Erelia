#include "erelia.h"

Battle_room_atlas* Battle_room_atlas::_instance = nullptr;

Battle_room_atlas::Battle_room_atlas()
{
	
}

jgl::Long Battle_room_atlas::request_new_battle_room_id()
{
	jgl::Long result = 0;
	for (; _battle_rooms.count(result) != 0; result++) {}
	return (result);
}

Battle_room* Battle_room_atlas::instanciate_new_room()
{
	jgl::Long new_id = request_new_battle_room_id();
	Battle_room* new_battle_room = new Battle_room(new_id);

	_battle_rooms[new_id] = new_battle_room;
	return (new_battle_room);
}

void Battle_room_atlas::add_room(jgl::Long p_id, Battle_room* p_room)
{
	if (_battle_rooms.count(p_id) != 0)
		delete _battle_rooms[p_id];
	_battle_rooms[p_id] = p_room;
}

Battle_room* Battle_room_atlas::battle_room(jgl::Long p_id)
{
	if (_battle_rooms.count(p_id) != 0)
		return (nullptr);
	return (_battle_rooms[p_id]);
}

Battle_room_atlas* Battle_room_atlas::instanciate()
{
	if (_instance == nullptr)
	{
		_instance = new Battle_room_atlas();
	}
	return (_instance);
}