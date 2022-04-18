#include "widget/Screen/Game_world/Widget/erelia_map_manager.h"
#include "widget/Screen/Game_world/erelia_game_world_screen.h"
#include "Widget/Commun/erelia_console_manager.h"
#include "structure/data/engine/erelia_engine.h"
#include "network/erelia_client_manager.h"
#include "network/erelia_server_manager.h"

jgl::Size_t Map_manager::nb_render = 0;
jgl::Size_t Map_manager::nb_update = 0;

void Map_manager::_on_geometry_change()
{
	if (Engine::instance() != nullptr && Engine::instance()->map() != nullptr)
		Engine::instance()->map()->unbake();
}

void Map_manager::_render()
{
	jgl::Vector2Int start = convert_screen_to_chunk(0);
	jgl::Vector2Int end = convert_screen_to_chunk(_area);
	Map* map = Engine::instance()->map();

	jgl::Int animation_state = (jgl::Application::active_application()->time() % 1000) / 250;

	if (Node::size < 4)
		animation_state = 0;

	if (map == nullptr)
		return;

	for (jgl::Int x = start.x; x <= end.x; x++)
	{
		for (jgl::Int y = start.y; y <= end.y; y++)
		{
			jgl::Vector2Int chunk_pos = jgl::Vector2Int(x, y);
			Chunk* tmp_chunk = map->chunk(chunk_pos);

			if (tmp_chunk != nullptr)
			{
				
				if (tmp_chunk->baked() == false)
					tmp_chunk->bake(map, true);

				tmp_chunk->render(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
				if (Game_world_screen::Publisher::instance()->context()->area_mode == true)
					tmp_chunk->render_area(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
				
			}
		}
	}
	nb_render++;
}

jgl::Bool Map_manager::_update()
{
	if (Engine::instance() == nullptr || Engine::instance()->map() == nullptr)
		return false;
	if (_update_timer.timeout() == true)
	{
		Map* map = Engine::instance()->map();

		jgl::Vector2Int start = convert_screen_to_chunk(0);
		jgl::Vector2Int end = convert_screen_to_chunk(_area);

		_asked_chunk_list.clear();

		for (jgl::Int x = start.x; x <= end.x; x++)
		{
			for (jgl::Int y = start.y; y <= end.y; y++)
			{
				jgl::Vector2Int chunk_pos = jgl::Vector2Int(x, y);

				if (map->chunk(chunk_pos) == nullptr && _asked_chunks[chunk_pos] == false)
				{
					_asked_chunks[chunk_pos] = true;
					_asked_chunk_list.push_back(chunk_pos);
				}
			}
		}

		if (_asked_chunk_list.size() != 0)
			_request_chunk_data();

		_update_timer.start();
		nb_update++;
	}

	return (false);
}

void Map_manager::_receive_chunk_data(Message& p_msg)
{
	while (p_msg.empty() == false)
	{
		jgl::Vector2Int chunk_pos;

		p_msg >> chunk_pos;

		Chunk* result = new Chunk(chunk_pos);

		result->mutex().lock();

		p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->content()), sizeof(jgl::Short) * Chunk::C_SIZE * Chunk::C_SIZE * Chunk::C_LAYER_LENGTH);
		p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->teleporter()), sizeof(jgl::Int) * Chunk::C_SIZE * Chunk::C_SIZE);

		result->mutex().unlock();

		Engine::instance()->map()->add_chunk(result);
		_asked_chunks[result->pos()] = false;

		for (jgl::Int i = -1; i <= 1; i++)
			for (jgl::Int j = -1; j <= 1; j++)
			{
				jgl::Vector2Int chunk_pos = result->pos() + jgl::Vector2Int(i, j);
				Chunk* tmp_chunk = Engine::instance()->map()->chunk(chunk_pos);
				if (tmp_chunk != nullptr)
					tmp_chunk->unbake();
			}

		
	}
}

void Map_manager::_request_chunk_data()
{
	Message msg(Server_message::Chunk_request);

	for (jgl::Size_t i = 0; i < _asked_chunk_list.size(); i++)
	{
		msg << _asked_chunk_list[i];
	}

	Client_manager::client()->send(msg);
}

void Map_manager::_treat_request_chunk_data(Connection* p_client, Message& p_msg)
{
	static Message result(Server_message::Chunk_data);

	result.clear();
	while (p_msg.empty() == false)
	{
		jgl::Vector2Int chunk_pos;

		p_msg >> chunk_pos;

		Chunk* tmp_chunk = Engine::instance()->map()->request_chunk(chunk_pos);

		result << chunk_pos;
		tmp_chunk->mutex().lock();
		result.add_in_array(reinterpret_cast<jgl::Uchar*>(tmp_chunk->content()), sizeof(jgl::Short) * Chunk::C_SIZE * Chunk::C_SIZE * Chunk::C_LAYER_LENGTH);
		result.add_in_array(reinterpret_cast<jgl::Uchar*>(tmp_chunk->teleporter()), sizeof(jgl::Int) * Chunk::C_SIZE * Chunk::C_SIZE);
		tmp_chunk->mutex().unlock();
	}

	p_client->send(result);
}

void Map_manager::_treat_chunk_modification(Connection* p_client, Message& p_msg)
{
	Server_manager::server()->send_to_all(p_msg, p_client);
}

void Map_manager::_received_chunk_modification(Message& p_msg)
{
	while (p_msg.empty() == false)
	{
		jgl::Vector3Int pos;
		jgl::Short value;

		p_msg >> pos >> value;

		jgl::Vector2Int chunk_pos = Map::convert_world_to_chunk(pos);
		if (Engine::instance()->map()->chunk(chunk_pos) != nullptr)
		{
			if (Engine::instance()->map()->content(pos) != value)
			{
				Engine::instance()->map()->place_node(pos, value);
			}
		}
	}
}

void Map_manager::_receive_place_teleport_data(Connection* p_client, Message& p_msg)
{
	jgl::Vector2Int source, destination;

	while (p_msg.empty() == false)
	{
		p_msg >> source;
		p_msg >> destination;

		jgl::Long id = Engine::instance()->request_teleporter_id();
		Engine::instance()->add_teleporter(id, destination);
		Engine::instance()->map()->place_teleporter(source, id);

		Console_manager::instance()->console_output()->add_message("Linking node [" + source.text() + "] and [" + destination.text() + "]");
	}
}

void Map_manager::_treat_place_teleport_data_request(Message& p_msg)
{
	static Message result(Server_message::Place_teleport_data);
	result.clear();

	jgl::Int type;

	p_msg >> type;

	if (Flag_item::pos.count(Flag_item::Color::Red) != 0 && Flag_item::pos.count(Flag_item::Color::Blue) != 0)
	{
		result << Flag_item::pos[Flag_item::Color::Red] << Flag_item::pos[Flag_item::Color::Blue];
		if (type == 2)
			result << Flag_item::pos[Flag_item::Color::Blue] << Flag_item::pos[Flag_item::Color::Red];
	}

	if (result.size() != 0)
		Client_manager::client()->send(result);
}

void Map_manager::_receive_remove_teleport_data(Connection* p_client, Message& p_msg)
{
	Console_manager::instance()->console_output()->add_message("Receive remove teleporter data");
	jgl::Vector2Int source;

	while (p_msg.empty() == false)
	{
		p_msg >> source;

		jgl::Long id = Engine::instance()->map()->teleporter(source);
		Engine::instance()->remove_teleporter(id);
		Engine::instance()->map()->place_teleporter(source, -1);

		Console_manager::instance()->console_output()->add_message("Removing teleporter [" + jgl::itoa(id) + "] from pos " + source.text());
	}
}

void Map_manager::_treat_remove_teleport_data_request(Message& p_msg)
{
	static Message result(Server_message::Remove_teleport_data);
	result.clear();

	Console_manager::instance()->console_output()->add_message("Treat remove teleporter data request");

	jgl::Int type;

	p_msg >> type;

	if (Flag_item::pos.count(Flag_item::Color::Red) != 0)
	{
		result << Flag_item::pos[Flag_item::Color::Red];
	}

	if (result.size() != 0)
	{
		Console_manager::instance()->console_output()->add_message("Sending remove teleporter data back to the server");
		Client_manager::client()->send(result);
	}
}

void Map_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Chunk_data, CLIENT_ACTIVITY{
			_receive_chunk_data(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Chunk_modification, CLIENT_ACTIVITY{
			_received_chunk_modification(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Place_teleport_data_request, CLIENT_ACTIVITY{
			_treat_place_teleport_data_request(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Remove_teleport_data_request, CLIENT_ACTIVITY{
			_treat_remove_teleport_data_request(p_msg);
		});
}

void Map_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Chunk_request, SERVER_ACTIVITY{
			_treat_request_chunk_data(p_client, p_msg);
		});

	Server_manager::server()->add_activity(Server_message::Chunk_modification, SERVER_ACTIVITY{
			_treat_chunk_modification(p_client, p_msg);
		});
	Server_manager::server()->add_activity(Server_message::Place_teleport_data, SERVER_ACTIVITY{
			_receive_place_teleport_data(p_client, p_msg);
		});
	Server_manager::server()->add_activity(Server_message::Remove_teleport_data, SERVER_ACTIVITY{
			_receive_remove_teleport_data(p_client, p_msg);
		});
}

Map_manager::Map_manager(jgl::Widget* p_parent) : Overworld_widget(p_parent),
	_update_timer(1)
{
	_initiate();
}