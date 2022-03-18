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
	jgl::cout << "Looking for a new index : result = " << result << jgl::endl;
	return (result);
}

void Engine::load_map(jgl::String p_world_path)
{
	_map->load(p_world_path);
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