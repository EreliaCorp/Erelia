#pragma once

#include "jgl.h"

#include "structure/Data/Monster/erelia_monster.h"

class Encounter_area
{
	jgl::Long _id;
	jgl::Array<std::pair<Monster*, jgl::Float>> _monsters;

public:
	Encounter_area(jgl::Long p_id)
	{
		_id = p_id;
	}

	jgl::Ulong id() { return (_id); }

	void add_monster(Monster* p_monster, jgl::Float p_percent)
	{
		_monsters.push_back(std::pair<Monster*, jgl::Float>(p_monster, p_percent));
	}

	Monster* monster(jgl::Float p_percent_value)
	{
		for (jgl::Size_t i = 0; i < _monsters.size(); i++)
		{
			if (p_percent_value < _monsters[i].second)
			{
				return (_monsters[i].first);
			}
			p_percent_value -= p_percent_value;
		}
		return (nullptr);
	}
};