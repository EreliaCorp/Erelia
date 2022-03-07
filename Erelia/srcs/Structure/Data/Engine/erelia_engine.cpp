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
	_entities[p_entity->id()] = p_entity;
}

void Engine::remove_entity(jgl::Long p_id)
{
	jgl::cout << "Removing entity id : " << jgl::endl;
	if (_player->id() == p_id)
		_player = nullptr;
	delete _entities[p_id];
	_entities.erase(p_id);
}

jgl::Long Engine::request_id()
{
	jgl::Long result = 0;
	for (; _entities.count(result) != 0; result++) {}
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