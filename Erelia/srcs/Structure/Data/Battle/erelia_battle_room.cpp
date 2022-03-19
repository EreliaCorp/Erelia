#include "erelia.h"

Battle_room::Battle_room(jgl::Long p_id)
{
	_id = p_id;
	for (jgl::Size_t i = 0; i < 2; i++)
	{
		for (jgl::Size_t j = 0; j < 4; j++)
		{
			_battler_slots[i][j] = nullptr;
		}
	}
}

void Battle_room::generate(Encounter_area::Encounter_data* p_encounter_area)
{
	for (jgl::Size_t i = 0; i < 4 && i < p_encounter_area->monster_datas.size(); i++)
	{
		Monster* tmp_monster = Monster_atlas::instance()->monster(p_encounter_area->monster_datas[i].id);
		if (tmp_monster != nullptr)
		{
			tmp_monster = tmp_monster->instanciate();
			tmp_monster->set_level(p_encounter_area->monster_datas[i].level);

			add_monster(Team::Red, static_cast<Slot>(i), tmp_monster);
		}
	}
}

void Battle_room::add_monster(Team p_team, Slot p_slot, Monster* p_monster)
{
	_battler_slots[static_cast<jgl::Int>(p_team)][static_cast<jgl::Int>(p_slot)] = p_monster;
}