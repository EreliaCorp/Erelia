#include "Structure/Data/Engine/erelia_engine.h"
#include "Structure/Atlas/erelia_path_atlas.h"

Engine::Engine()
{
	_player = new Player();
	_map = new Map();
}

void Engine::initialize_player(jgl::Long p_id)
{
	_player->set_id(p_id);
	add_entity(_player);
}

Entity* Engine::entity(jgl::Long p_id)
{
	if (_entities.count(p_id) == 0)
		return (nullptr);
	return (_entities[p_id]);
}

void Engine::add_entity(Entity* p_entity)
{
	if (_entities[p_entity->id()] != nullptr)
		delete _entities[p_entity->id()];
	_entities[p_entity->id()] = p_entity;
}

void Engine::remove_entity(jgl::Long p_id)
{
	if (_player->id() == p_id)
		_player = nullptr;
	delete _entities[p_id];
	_entities.erase(p_id);
}

Encounter_area* Engine::encounter_area(jgl::Long p_id)
{
	if (_encounter_areas.count(p_id) == 0)
		return (nullptr);
	return (_encounter_areas[p_id]);
}

void Engine::add_encounter_area(Encounter_area* p_area)
{
	if (_encounter_areas[p_area->id()] != nullptr)
		delete _encounter_areas[p_area->id()];
	_encounter_areas[p_area->id()] = p_area;
}

void Engine::remove_encounter_area(jgl::Long p_id)
{
	delete _encounter_areas[p_id];
	_encounter_areas.erase(p_id);
}

jgl::Long Engine::request_id()
{
	jgl::Long result = 0;
	for (; _entities.count(result) != 0; result++) {}
	return (result);
}

jgl::Long Engine::request_monster_area_id()
{
	jgl::Long result = 0;
	for (; _encounter_areas.count(result) != 0; result++) {}
	return (result);
}

void Engine::save()
{
	save_map();
	save_area();
	save_wrap();
}

void Engine::load()
{
	load_map();
	load_area();
	load_wrap();
}

void Engine::save_map()
{
	_map->save();
}

void Engine::load_map()
{
	_map->load();
}

void Engine::load_area()
{
	jgl::Array<jgl::String> file_list = jgl::list_files(Path_atlas::world_path + Path_atlas::encounter_area_subpath, Path_atlas::encounter_area_extension);

	for (jgl::Size_t i = 0; i < file_list.size(); i++)
	{
		Encounter_area* new_encounter = new Encounter_area();
		
		new_encounter->load(file_list[i]);

		jgl::cout << "Loading encounter area [" << new_encounter->id() << "]" << jgl::endl;

		_encounter_areas[new_encounter->id()] = new_encounter;
	}
}

void Engine::save_area()
{
	for (auto tmp : _encounter_areas)
	{
		tmp.second->save(Path_atlas::world_path + Path_atlas::encounter_area_subpath + Path_atlas::encounter_area_name + jgl::itoa(tmp.first) + Path_atlas::encounter_area_extension);
	}
}

void Engine::load_wrap()
{
	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::wrap_sub_path + Path_atlas::wrap_name_file + Path_atlas::wrap_save_extension, jgl::File_mode::in);

	while (file.peek() != EOF)
	{
		static jgl::Array<jgl::String> tab;
		jgl::String line = jgl::get_str(file);
		line.split(tab, ";");
		if (tab.size() == 3 && tab[1].compose_only("0123456789-") && tab[2].compose_only("0123456789-"))
		{
			_wraps[tab[0]] = jgl::Vector2Int(jgl::stoi(tab[1]), jgl::stoi(tab[2]));
		}
		else
		{
			THROW_INFORMATION("Error while loading wrap : " + line);
		}
	}
}

void Engine::save_wrap()
{
	THROW_INFORMATION("Saving wrap");

	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::wrap_sub_path + Path_atlas::wrap_name_file + Path_atlas::wrap_save_extension, jgl::File_mode::out);

	for (auto tmp : _wraps)
	{
		THROW_INFORMATION("Saving wrap [" + tmp.first + "]");
		file << tmp.first << ";" << tmp.second.x << ";" << tmp.second.y << std::endl;
	}
}