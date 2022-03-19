#pragma once

#include "jgl.h"

#include "structure/Data/Map/erelia_encounter_area.h"
#include "structure/Data/Monster/erelia_monster.h"

class Battle_room
{
public:
	enum class Team
	{
		Red = 0,
		Blue = 1
	};
	enum class Slot
	{
		SlotA = 0,
		SlotB = 1,
		SlotC = 2,
		SlotD = 3
	};
private:
	jgl::Long _id;
	Monster* _battler_slots[2][4];

public:
	Battle_room(jgl::Long p_id);
	void generate(Encounter_area::Encounter_data* p_encounter_area);
	void add_monster(Team p_team, Slot p_slot, Monster* p_monster);
};