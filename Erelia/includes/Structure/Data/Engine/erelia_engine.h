#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_player.h"

class Engine
{
private:
	static Engine* _instance;

	Map* _map;
	Player* _player;

	jgl::Map<jgl::Long, Entity*> _entities;

	Engine();

public:
	Map* map() { return (_map); }
	Player* player() { return (_player); }

	void initialize_player(Player* p_player);
	void add_entity(Entity* p_entity);

	void load_map(jgl::String p_world_path);

	static Engine* instanciate();

	static Engine* instance();
};