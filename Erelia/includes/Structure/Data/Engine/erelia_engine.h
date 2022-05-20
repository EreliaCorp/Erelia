#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_map.h"
#include "Structure/Data/Entity/erelia_AI_controlled_entity.h"
#include "structure/data/entity/erelia_spawner.h"
#include "Structure/Data/Entity/erelia_player.h"
#include "Structure/Data/Entity/erelia_enemy.h"
#include "Structure/Data/Entity/erelia_NPC.h"

class Engine : public jgl::Singleton<Engine>
{
	friend class jgl::Singleton<Engine>;
private:
	Map* _map;
	Player* _player;

	std::recursive_mutex _entities_mutex;

	jgl::Map<jgl::String, jgl::Vector2Int> _wraps;

	jgl::Map<jgl::Long, Entity*> _entities;
	jgl::Array<AI_controlled_entity*> _NPC_entities;
	jgl::Array<Spawner*> _spawner_entities;

	jgl::Map<jgl::Long, jgl::Vector2Int> _teleporter_destination;

	Engine();

	void _update_entity();
	void _update_NPC();
	void _update_spawner();

	jgl::String _load_entity_name(jgl::File& p_file);
	Entity::Type _load_entity_type(jgl::File& p_file);
	jgl::Vector2Int _load_entity_pos(jgl::File& p_file);
	jgl::Ulong _load_entity_move_speed(jgl::File& p_file);
	void _load_entity_flags(jgl::Array<jgl::Vector2Int>& p_tab, jgl::File& p_file);
	void _load_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::Vector2Int p_base, jgl::File& p_file);
	void _load_static_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file);
	void _load_wander_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file);
	void _load_path_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file);

	void _load_NPC(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file);
	void _load_spawner(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file);
	void _load_enemy(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file);

public:
	void update();

	void lock_entities()
	{
		_entities_mutex.lock();
	}
	void unlock_entities()
	{
		_entities_mutex.unlock();
	}

	Entity* entity_collision(Entity* p_entity, jgl::Vector2Int p_pos);

	Map* map() { return (_map); }
	Player* player() { return (_player); }

	jgl::Map<jgl::String, jgl::Vector2Int>& wraps() { return (_wraps); }
	jgl::Map<jgl::Long, Entity*>& entities() { return (_entities); }

	void initialize_player(jgl::String p_name, jgl::Long p_id);
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

	void save_entity();
	void load_entity();
};