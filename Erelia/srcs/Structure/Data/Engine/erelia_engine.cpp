#include "erelia.h"

Engine* Engine::_instance = nullptr;

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
}

void Engine::load()
{
	load_map();
	load_area();
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

Engine* Engine::instanciate()
{
	if (_instance == nullptr)
		_instance = new Engine();
	return (_instance);
}

Engine* Engine::instance()
{
	return (_instance);
}