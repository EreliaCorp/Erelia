#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_player.h"

class Engine : public jgl::Singleton<Engine>
{
	friend class jgl::Singleton<Engine>;
private:
	Map* _map;
	Player* _player;

	jgl::Map<jgl::String, jgl::Vector2Int> _wraps;

	jgl::Map<jgl::Long, Entity*> _entities;
	jgl::Array<Entity*> _NPC_entities;

	jgl::Map<jgl::Long, jgl::Vector2Int> _teleporter_destination;

	Engine();

	void _update_entity();
	void _update_NPC();

public:
	void update();

	Map* map() { return (_map); }
	Player* player() { return (_player); }

	jgl::Map<jgl::String, jgl::Vector2Int>& wraps() { return (_wraps); }
	jgl::Map<jgl::Long, Entity*>& entities() { return (_entities); }

	void initialize_player(jgl::Long p_id);
	Entity* entity(jgl::Long p_id);
	void add_entity(Entity* p_entity);
	void remove_entity(jgl::Long p_id);

	jgl::Vector2Int teleporter(jgl::Long p_id);
	void add_teleporter(jgl::Long p_id, jgl::Vector2Int p_destination);
	void remove_teleporter(jgl::Long p_id);

	jgl::Long request_id();
	jgl::Long request_teleporter_id();

	void save();
	void load();

	void save_map();
	void load_map();

	void load_wrap();
	void save_wrap();

	void save_teleport();
	void load_teleport();
};