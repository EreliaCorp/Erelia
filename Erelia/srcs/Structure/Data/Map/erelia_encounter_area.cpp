#include "erelia.h"

Encounter_area::Encounter_area(jgl::Long p_id)
{
	_id = p_id;
}

void Encounter_area::Encounter_data::save(jgl::File& p_file)
{
	p_file << percent << ";";
	for (jgl::Size_t i = 0; i < monster_datas.size(); i++)
	{
		if (i != 0)
			p_file << "/";
		p_file << monster_datas[i].id << ":" << monster_datas[i].level;
	}
	p_file << std::endl;
}

void Encounter_area::Encounter_data::load(jgl::File& p_file)
{
	static jgl::Array<jgl::String> tab;
	static jgl::Array<jgl::String> tab_monster_info;
	static jgl::Array<jgl::String> tab_monster_data;

	jgl::get_str(p_file).split(tab, ";");

	percent = jgl::stof(tab[0]);
	tab[1].split(tab_monster_info, "/");
	for (jgl::Size_t i = 0; i < tab_monster_info.size(); i++)
	{
		tab_monster_info[i].split(tab_monster_data, ":");
		Monster_data monster_data;

		monster_data.id = jgl::stoi(tab_monster_data[0]);
		monster_data.level = jgl::stoi(tab_monster_data[1]);

		monster_datas.push_back(monster_data);
	}
}

void Encounter_area::save(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::out);

	file << _id << std::endl;
	for (jgl::Size_t i = 0; i < _monsters.size(); i++)
	{
		_monsters[i]->save(file);
	}
}

void Encounter_area::load(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

	_id = jgl::stoi(jgl::get_str(file));
	while (file.peek() != EOF)
	{
		Encounter_data* new_encounter_data = new Encounter_area::Encounter_data();

		new_encounter_data->load(file);

		_monsters.push_back(new_encounter_data);
	}
}

Encounter_area::Encounter_data* Encounter_area::monster(jgl::Float p_percent_value)
{
	for (jgl::Size_t i = 0; i < _monsters.size(); i++)
	{
		if (p_percent_value < _monsters[i]->percent)
		{
			return (_monsters[i]);
		}
		p_percent_value -= _monsters[i]->percent;
	}
	return (nullptr);
}