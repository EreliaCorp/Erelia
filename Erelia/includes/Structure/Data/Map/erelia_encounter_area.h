#pragma once

#include "jgl.h"

#include "structure/Data/Monster/erelia_monster.h"

class Encounter_area
{
	struct Encounter_data
	{
		jgl::Uint monster_id;
		jgl::Float percent;

		void save(jgl::File& p_file);
		void load(jgl::File& p_file);
	};

	jgl::Long _id;
	jgl::Array<Encounter_data> _monsters;

public:
	Encounter_area(jgl::Long p_id = -1);

	void save(jgl::String p_path);
	void load(jgl::String p_path);

	jgl::Long id() { return (_id); }

	void add_monster(jgl::Uint p_monster_id, jgl::Float p_percent);
	jgl::Array<Encounter_data>& monsters(){return (_monsters);}
	jgl::Uint monster(jgl::Float p_percent_value);
};