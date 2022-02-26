#include "erelia.h"

Engine* Engine::_instance = nullptr;

Engine::Engine()
{
	_player = nullptr;
	_map = new Map();
}

void Engine::initialize_player(Player* p_player)
{
	_player = p_player;
	_entities[p_player->id()] = p_player;
}

void Engine::add_entity(Entity* p_entity)
{

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