#include "erelia.h"

Engine* Engine::_instance = nullptr;

Engine::Engine()
{
	_player = new Player();
}

void Engine::load_map(jgl::String p_world_path)
{

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