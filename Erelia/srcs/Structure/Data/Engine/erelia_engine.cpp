#include "Structure/Data/Engine/erelia_engine.h"
#include "Structure/Atlas/erelia_path_atlas.h"
#include "Network/erelia_server_manager.h"

Engine::Engine()
{
	_player = new Player("Player");
	_map = new Map();
}

void Engine::_update_entity()
{
	for (auto tmp : _entities)
	{
		if (tmp.second->is_moving() == true)
		{
			tmp.second->update_pos();

			if (tmp.second->is_moving() == false)
			{
				jgl::Long teleporter_id = Engine::instance()->map()->teleporter(tmp.second->destination());
				if (teleporter_id >= 0)
				{
					jgl::Vector2 delta = tmp.second->movement();
					tmp.second->place(Engine::instance()->teleporter(teleporter_id));
					tmp.second->move(tmp.second->movement());
				}
			}
		}
	}
}

void Engine::_update_NPC()
{
	for (jgl::Size_t i = 0; i < _NPC_entities.size(); i++)
	{
		_NPC_entities[i]->update();
	}
}

void Engine::update()
{
	if (Server_manager::server() != nullptr)
		_update_NPC();
	_update_entity();
}

Entity* Engine::entity_collision(Entity* p_entity, jgl::Vector2Int p_pos)
{
	if (p_entity != nullptr && p_entity->is_flying() == true)
		return (nullptr);

	for (auto tmp : _entities)
	{
		Entity* tmp_entity = tmp.second;
		if (tmp_entity != p_entity && tmp_entity->pos().distance(p_pos) < 1.0f)
			return (tmp_entity);
	}

	return (nullptr);
}

void Engine::initialize_player(jgl::String p_name, jgl::Long p_id)
{
	_player->set_name(p_name);
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
	if (p_entity->type() != Entity::Type::Player)
		_NPC_entities.push_back(static_cast<AI_controlled_entity*>(p_entity));
}

void Engine::remove_entity(jgl::Long p_id)
{
	if (_entities.count(p_id) != 0)
	{
		auto tmp_entity = _NPC_entities.find(static_cast<AI_controlled_entity*>(_entities[p_id]));
		if (tmp_entity != _NPC_entities.end())
			_NPC_entities.erase(tmp_entity);
	}
	if (_player->id() == p_id)
		_player = nullptr;
	delete _entities[p_id];
	_entities.erase(p_id);
}

jgl::Vector2Int Engine::teleporter(jgl::Long p_id)
{
	if (_teleporter_destination.count(p_id) == 0)
		return (-1);
	return (_teleporter_destination[p_id]);
}

void Engine::add_teleporter(jgl::Long p_id, jgl::Vector2Int p_destination)
{
	_teleporter_destination[p_id] = p_destination;
}

void Engine::remove_teleporter(jgl::Long p_id)
{
	_teleporter_destination.erase(p_id);
}

jgl::Long Engine::request_id()
{
	jgl::Long result = 0;
	for (; _entities.count(result) != 0; result++) {}
	return (result);
}

jgl::Long  Engine::request_teleporter_id()
{
	jgl::Long result = 0;
	for (; _teleporter_destination.count(result) != 0; result++) {}
	return (result);
}

void Engine::save()
{
	save_map();
	save_wrap();
	save_teleport();
	save_entity();
}

void Engine::load()
{
	load_map();
	load_wrap();
	load_teleport();
	load_entity();
}

void Engine::save_map()
{
	_map->save();
}

void Engine::load_map()
{
	_map->load();
}

void Engine::load_wrap()
{
	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::wrap_sub_path + Path_atlas::wrap_name_file + Path_atlas::wrap_save_extension, jgl::File_mode::in);

	while (file.peek() != EOF)
	{
		static jgl::Array<jgl::String> tab;
		jgl::String line = jgl::get_str(file);
		line.split(tab, ";");
		if (tab.size() == 3 && tab[1].compose_only("0123456789-") && tab[2].compose_only("0123456789-"))
		{
			_wraps[tab[0]] = jgl::Vector2Int(jgl::stoi(tab[1]), jgl::stoi(tab[2]));
		}
		else
		{
			THROW_INFORMATION("Error while loading wrap : " + line);
		}
	}
}

void Engine::save_wrap()
{
	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::wrap_sub_path + Path_atlas::wrap_name_file + Path_atlas::wrap_save_extension, jgl::File_mode::out);

	for (auto tmp : _wraps)
	{
		file << tmp.first << ";" << tmp.second.x << ";" << tmp.second.y << std::endl;
	}
}

void Engine::save_teleport()
{
	THROW_INFORMATION("Saving teleporter");

	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::teleporter_sub_path + Path_atlas::teleporter_name_file + Path_atlas::teleporter_save_extension, jgl::File_mode::out);

	for (auto tmp : _teleporter_destination)
	{
		file.write(reinterpret_cast<const char*>(&tmp.first), sizeof(jgl::Long));
		file.write(reinterpret_cast<const char*>(&tmp.second.x), sizeof(jgl::Int));
		file.write(reinterpret_cast<const char*>(&tmp.second.y), sizeof(jgl::Int));
	}
}

void Engine::load_teleport()
{
	if (jgl::check_file_exist(Path_atlas::world_path + Path_atlas::teleporter_sub_path + Path_atlas::teleporter_name_file + Path_atlas::teleporter_save_extension) == false)
		return;

	jgl::File file = jgl::open_file(Path_atlas::world_path + Path_atlas::teleporter_sub_path + Path_atlas::teleporter_name_file + Path_atlas::teleporter_save_extension, jgl::File_mode::in);

	while (file.peek() != EOF)
	{
		jgl::Long id;
		jgl::Vector2Int pos;

		file.read(reinterpret_cast<char*>(&id), sizeof(jgl::Long));
		file.read(reinterpret_cast<char*>(&pos.x), sizeof(jgl::Int));
		file.read(reinterpret_cast<char*>(&pos.y), sizeof(jgl::Int));

		THROW_INFORMATION("Placing new teleporter [" + jgl::itoa(id) + "] at destination " + pos.text());
		Engine::instance()->add_teleporter(id, pos);
	}
}

void Engine::save_entity()
{
	
}

jgl::String Engine::_load_entity_name(jgl::File& p_file)
{
	return (jgl::get_str(p_file));
}

Entity::Type Engine::_load_entity_type(jgl::File& p_file)
{
	jgl::String line = jgl::get_str(p_file);

	if (line == "NPC")
		return (Entity::Type::NPC);
	else if (line == "Spawner")
		return(Entity::Type::Spawner);
	return (Entity::Type::Enemy);
}

jgl::Vector2Int Engine::_load_entity_pos(jgl::File& p_file)
{
	static jgl::Array<jgl::String> tab;

	jgl::get_str(p_file).split(tab, ";");

	return (jgl::Vector2Int(jgl::stoi(tab[0]), jgl::stoi(tab[1])));

}

jgl::Ulong Engine::_load_entity_move_speed(jgl::File& p_file)
{
	return (jgl::stoi(jgl::get_str(p_file)));
}

void Engine::_load_entity_flags(jgl::Array<jgl::Vector2Int>& p_tab, jgl::File& p_file)
{
	p_tab.clear();

	static jgl::Array<jgl::String> tab;
	static jgl::Array<jgl::String> sub_tab;

	jgl::get_str(p_file).split(tab, "/");

	for (jgl::Size_t i = 0; i < tab.size(); i++)
	{
		tab[i].split(sub_tab, ";");

		p_tab.push_back(jgl::Vector2Int(jgl::stoi(sub_tab[0]), jgl::stoi(sub_tab[1])));
	}
}

void Engine::_load_static_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file)
{
	p_param.pattern = AI_controlled_entity::Movement_info::Pattern::Static;
}

void Engine::_load_wander_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file)
{
	static jgl::Array<jgl::String> tab;

	tab.clear();
	p_param.pattern = AI_controlled_entity::Movement_info::Pattern::Wander;
	p_param.data.range = jgl::stoi(jgl::get_str(p_file));
}

void Engine::_load_path_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::File& p_file)
{
	p_param.pattern = AI_controlled_entity::Movement_info::Pattern::Path;
}

void Engine::_load_movement_pattern(AI_controlled_entity::Movement_info& p_param, jgl::Vector2Int p_base, jgl::File& p_file)
{
	p_param.data.timer = jgl::Timer(jgl::stoi(jgl::get_str(p_file)));

	jgl::String line = jgl::get_str(p_file);

	p_param.data.base = p_base;

	if (line == "Static")
		_load_static_movement_pattern(p_param, p_file);
	else if (line == "Wander")
		_load_wander_movement_pattern(p_param, p_file);
	else if (line == "Path")
		_load_path_movement_pattern(p_param, p_file);
}

void Engine::_load_NPC(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file)
{
	NPC* new_NPC = new NPC(p_name, request_id());
	THROW_INFORMATION("Creating NPC (" + p_name + ") of id " + jgl::itoa(new_NPC->id()) + " at pos [" + p_pos.text() + "]");
	new_NPC->set_move_speed(p_move_speed);
	new_NPC->place(p_pos);
	_load_movement_pattern(new_NPC->movement_info(), p_pos, p_file);
	add_entity(new_NPC);
}

void Engine::_load_spawner(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file)
{
	Entity* new_entity = new Entity(p_name, Entity::Type::Spawner, request_id());
	new_entity->set_move_speed(p_move_speed);
	new_entity->place(p_pos);
	add_entity(new_entity);
}

void Engine::_load_enemy(jgl::String p_name, jgl::Vector2Int p_pos, jgl::Ulong p_move_speed, jgl::File& p_file)
{
	Entity* new_entity = new Entity(p_name, Entity::Type::Enemy, request_id());
	new_entity->set_move_speed(p_move_speed);
	new_entity->place(p_pos);
	add_entity(new_entity);
}

void Engine::load_entity()
{
	jgl::Array<jgl::String> files_path = jgl::list_files(Path_atlas::world_path + Path_atlas::entity_sub_path, Path_atlas::entity_extension);
	jgl::Array<jgl::String> tab;

	for (jgl::Size_t i = 0; i < files_path.size(); i++)
	{
		jgl::File file = jgl::open_file(files_path[i], jgl::File_mode::in);

		jgl::String name = _load_entity_name(file);
		Entity::Type type = _load_entity_type(file);
		jgl::Vector2Int pos = _load_entity_pos(file);
		jgl::Ulong move_speed = _load_entity_move_speed(file);

		if (type == Entity::Type::NPC)
		{
			_load_NPC(name, pos, move_speed, file);
		}
		else if (type == Entity::Type::Spawner)
		{
			_load_spawner(name, pos, move_speed, file);
		}
		else if (type == Entity::Type::Enemy)
		{
			_load_enemy(name, pos, move_speed, file);
		}
		else
		{
			THROW_EXCEPTION(jgl::Error_level::Error, 1, "Bad entity type");
		}

		static jgl::Array<jgl::Vector2Int> flags_pos;
		_load_entity_flags(flags_pos, file);

	}
}