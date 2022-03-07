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

	jgl::Map<jgl::Long, Entity*>& entities() { return (_entities); }

	void initialize_player(jgl::Long p_id);
	Entity* entity(jgl::Long p_id);
	void add_entity(Entity* p_entity);
	void remove_entity(jgl::Long p_id);

	jgl::Long request_id();

	void load_map(jgl::String p_world_path);

	static Engine* instanciate();

	static Engine* instance();
};