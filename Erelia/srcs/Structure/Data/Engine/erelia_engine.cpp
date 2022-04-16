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
	{
		delete _entities[p_entity->id()];
	}
	_entities[p_entity->id()] = p_entity;
	if (p_entity->type() == Entity::Type::NPC || p_entity->type() == Entity::Type::Spawner)
		_NPC_entities.push_back(p_entity);
}

void Engine::remove_entity(jgl::Long p_id)
{
	if (_entities.count(p_id) != 0)
	{
		auto tmp_entity = _NPC_entities.find(_entities[p_id]);
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
	for (jgl::Size_t i = 0; i < _NPC_entities.size(); i++)
	{
		jgl::File myfile = jgl::open_file(Path_atlas::world_path + Path_atlas::entity_sub_path + _NPC_entities[i]->name() + jgl::itoa(i) + Path_atlas::entity_extension, jgl::File_mode::out);
	}
}

void Engine::load_entity()
{
	jgl::Array<jgl::String> files_path = jgl::list_files(Path_atlas::world_path + Path_atlas::entity_sub_path, Path_atlas::entity_extension);
	jgl::Array<jgl::String> tab;

	for (jgl::Size_t i = 0; i < files_path.size(); i++)
	{
		jgl::cout << "Loading file [" << files_path[i] << "]" << jgl::endl;
		jgl::File file = jgl::open_file(files_path[i], jgl::File_mode::in);

		jgl::String name = jgl::get_str(file);
		Entity::Type type = static_cast<Entity::Type>(jgl::stoi(jgl::get_str(file)));

		tab = jgl::get_strsplit(file, ";", 2);
		jgl::Vector2Int pos = jgl::Vector2Int(jgl::stoi(tab[0]), jgl::stoi(tab[1]));

		if (type == Entity::Type::NPC)
		{
			NPC* new_npc = new NPC(name, request_id());
			new_npc->place(pos);
			add_entity(new_npc);
		}
		else if (type == Entity::Type::Spawner)
		{
			Entity* new_entity = new Entity(name, type, request_id());
			new_entity->place(pos);
			add_entity(new_entity);
		}
		else
		{
			jgl::cout << "Error in file [" << files_path[i] << "]" << jgl::endl;
		}
	}
}