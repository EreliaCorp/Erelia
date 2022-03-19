#pragma once

#include "jgl.h"

#include "structure/Data/Monster/erelia_monster.h"

class Encounter_area
{
public:
	struct Encounter_data
	{
		struct Monster_data
		{
			jgl::Uint id;
			jgl::Uint level;
		};
		jgl::Array<Monster_data> monster_datas;
		jgl::Float percent;

		void save(jgl::File& p_file);
		void load(jgl::File& p_file);
	};

private:
	jgl::Long _id;
	jgl::Array<Encounter_data *> _monsters;

public:
	Encounter_area(jgl::Long p_id = -1);

	void save(jgl::String p_path);
	void load(jgl::String p_path);

	jgl::Long id() { return (_id); }

	jgl::Array<Encounter_data*>& monsters(){return (_monsters);}
	Encounter_data* monster(jgl::Float p_percent_value);
};