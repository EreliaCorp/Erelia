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

	jgl::Map<jgl::Long, Encounter_area*> _encounter_areas;

	Engine();

public:
	Map* map() { return (_map); }
	Player* player() { return (_player); }

	jgl::Map<jgl::Long, Entity*>& entities() { return (_entities); }
	jgl::Map<jgl::Long, Encounter_area*>& encounter_areas() { return (_encounter_areas); }

	void initialize_player(jgl::Long p_id);
	Entity* entity(jgl::Long p_id);
	void add_entity(Entity* p_entity);
	void remove_entity(jgl::Long p_id);

	Encounter_area* encounter_area(jgl::Long p_id);
	void add_encounter_area(Encounter_area* p_area);
	void remove_encounter_area(jgl::Long p_id);

	jgl::Long request_id();
	jgl::Long request_monster_area_id();

	void save();
	void load();

	void save_map();
	void load_map();

	void load_area();
	void save_area();

	static Engine* instanciate();

	static Engine* instance();
};