#include "Structure/Data/Engine/erelia_engine.h"
#include "Structure/Atlas/erelia_path_atlas.h"
#include "Network/erelia_server_manager.h"

Engine::Engine()
{
	_player = new Player();
	_map = new Map();
}

void Engine::_update_entity()
{
	for (auto tmp : Engine::instance()->entities())
	{
		if (tmp.second->is_moving() == true)
		{
			tmp.second->update();

			if (tmp.second->is_moving() == false)
			{
				jgl::Long teleporter_id = Engine::instance()->map()->teleporter(tmp.second->destination());
				if (teleporter_id != -1)
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
		Entity* tmp_entity = _NPC_entities[i];
		if (tmp_entity->type() == Entity::Type::NPC && tmp_entity->is_moving() == false && Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), jgl::Vector2(1, 1)) == true)
		{
			tmp_entity->move(jgl::Vector2(1, 1));
		}
		else if (tmp_entity->type() == Entity::Type::Enemy && tmp_entity->is_moving() == false && Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), jgl::Vector2(0, 1)) == true)
		{
			tmp_entity->move(jgl::Vector2(0, 1));
		}
	}
}

void Engine::update()
{
	if (Server_manager::server() != nullptr)
		_update_NPC();
	_update_entity();
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
	if (p_entity->type() != Entity::Type::Player)
		_NPC_entities.push_back(p_entity);
}

void Engine::remove_entity(jgl::Long p_id)
{
	if (_entities.count(p_id) != 0)
	{
		Entity* tmp_entity = _entities[p_id];
		_NPC_entities.erase(_NPC_entities.find(tmp_entity));
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
}

void Engine::load()
{
	load_map();
	load_wrap();
	load_teleport();
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