#include "erelia.h"

Battle_manager* Battle_manager::_instance = nullptr;

void Battle_manager::_on_geometry_change()
{

}

void Battle_manager::_render()
{

}

jgl::Bool Battle_manager::_update()
{
	return (false);
}

Battle_manager::Battle_manager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_initiate();
}

void Battle_manager::_send_command()
{

}

void Battle_manager::_initialize_server()
{
	Battle_room_atlas::instanciate();
}

void Battle_manager::_initialize_client()
{

}

void Battle_manager::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();
	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Battle_room* Battle_manager::generate_battle_room(Encounter_area* p_encounter_area)
{
	if (p_encounter_area == nullptr)
		return (nullptr);

	Battle_room* new_battle_room = nullptr;

	jgl::Float percent = static_cast<jgl::Float>(jgl::generate_nbr(0, 100000)) / 1000.0f;

	for (jgl::Size_t i = 0; i < p_encounter_area->monsters().size() && new_battle_room == nullptr; i++)
	{
		if (percent < p_encounter_area->monsters()[i]->percent)
		{
			new_battle_room = Battle_room_atlas::instance()->instanciate_new_room();
			new_battle_room->generate(p_encounter_area->monster(i));
		}
		else
		{
			percent -= p_encounter_area->monsters()[i]->percent;
		}
	}

	return (new_battle_room);
}

void Battle_manager::set_battle_room(Battle_room* p_battle_room)
{
	_active_battle_room = p_battle_room;
}

void Battle_manager::start_battle_room(Battle_room* p_battle_room)
{
	static Message msg(Server_message::Battle_start_notification);

	msg.clear();




}

Battle_manager* Battle_manager::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Battle_manager(p_parent);
	}
	return (_instance);
}

Battle_manager* Battle_manager::instance()
{
	return (_instance);
}
