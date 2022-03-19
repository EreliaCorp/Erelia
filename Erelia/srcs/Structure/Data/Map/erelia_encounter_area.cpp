#include "erelia.h"

Encounter_area::Encounter_area(jgl::Long p_id)
{
	_id = p_id;
}

void Encounter_area::Encounter_data::save(jgl::File& p_file)
{
	p_file << monster_id << std::endl;
	p_file << percent << std::endl;
}

void Encounter_area::Encounter_data::load(jgl::File& p_file)
{
	monster_id = jgl::stoi(jgl::get_str(p_file));
	percent = jgl::stof(jgl::get_str(p_file));
}

void Encounter_area::save(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::out);

	file << _id << std::endl;
	for (jgl::Size_t i = 0; i < _monsters.size(); i++)
	{
		_monsters[i].save(file);
	}
}

void Encounter_area::load(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

	_id = jgl::stoi(jgl::get_str(file));
	while (file.peek() != EOF)
	{
		Encounter_data new_encounter_data;

		new_encounter_data.load(file);

		_monsters.push_back(new_encounter_data);
	}
}

void Encounter_area::add_monster(jgl::Uint p_monster_id, jgl::Float p_percent)
{
	Encounter_data new_encounter;

	new_encounter.monster_id = p_monster_id;
	new_encounter.percent = p_percent;

	_monsters.push_back(new_encounter);
}

jgl::Uint Encounter_area::monster(jgl::Float p_percent_value)
{
	for (jgl::Size_t i = 0; i < _monsters.size(); i++)
	{
		if (p_percent_value < _monsters[i].percent)
		{
			return (_monsters[i].monster_id);
		}
		p_percent_value -= _monsters[i].percent;
	}
	return (0);
}