#include "widget/Screen/Game_world/Widget/erelia_map_manager.h"
#include "widget/Screen/Game_world/erelia_game_world_screen.h"
#include "structure/data/engine/erelia_engine.h"
#include "network/erelia_client_manager.h"
#include "network/erelia_server_manager.h"

void Map_manager::_on_geometry_change()
{

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
				_map_mutex.lock();
				if (tmp_chunk->baked() == false)
					tmp_chunk->bake(map, true);

				jgl::cout << "Render chunk [" << chunk_pos << "]" << jgl::endl;
				tmp_chunk->render(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
				if (Game_world_screen::Publisher::instance()->context()->area_mode == true)
					tmp_chunk->render_area(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
				_map_mutex.unlock();
			}
		}
	}
}

jgl::Bool Map_manager::_update()
{
	if (Engine::instance() == nullptr || Engine::instance()->map() == nullptr)
		return false;
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

	return (false);
}

void Map_manager::_receive_chunk_data(Message& p_msg)
{
	while (p_msg.empty() == false)
	{
		jgl::Vector2Int chunk_pos;

		p_msg >> chunk_pos;

		Chunk* result = new Chunk(chunk_pos);
		p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->content()), sizeof(jgl::Short) * Chunk::C_SIZE * Chunk::C_SIZE * Chunk::C_LAYER_LENGTH);
		p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->encounter()), sizeof(jgl::Int) * Chunk::C_SIZE * Chunk::C_SIZE);


		_map_mutex.lock();
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

		_map_mutex.unlock();
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
		result.add_in_array(reinterpret_cast<jgl::Uchar*>(tmp_chunk->content()), sizeof(jgl::Short) * Chunk::C_SIZE * Chunk::C_SIZE * Chunk::C_LAYER_LENGTH);
		result.add_in_array(reinterpret_cast<jgl::Uchar*>(tmp_chunk->encounter()), sizeof(jgl::Int) * Chunk::C_SIZE * Chunk::C_SIZE);
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

void Map_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Chunk_data, CLIENT_ACTIVITY{
			_receive_chunk_data(p_msg);
		});

	Client_manager::client()->add_activity(Server_message::Chunk_modification, CLIENT_ACTIVITY{
			_received_chunk_modification(p_msg);
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
}

Map_manager::Map_manager(jgl::Widget* p_parent) : Overworld_widget(p_parent)
{
	_initiate();
}