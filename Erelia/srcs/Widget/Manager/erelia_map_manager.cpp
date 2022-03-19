#include "erelia.h"

std::mutex Map_manager::_map_mutex;
Map_manager* Map_manager::_instance = nullptr;

void Map_manager::_on_geometry_change()
{

}

void Map_manager::_render()
{
	if (Engine::instance()->player() == nullptr || Engine::instance()->map() == nullptr)
		return;

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
			_map_mutex.lock();
			Chunk* tmp_chunk = map->chunk(chunk_pos);

			if (tmp_chunk != nullptr)
			{
				if (tmp_chunk->baked() == false)
					tmp_chunk->bake(map, true);

				tmp_chunk->render(jgl::convert_screen_to_opengl(convert_chunk_to_screen(chunk_pos), _depth), animation_state);
			}
			_map_mutex.unlock();
		}
	}
}

void Map_manager::receive_chunk(Chunk* p_chunk)
{
	_map_mutex.lock();
	Engine::instance()->map()->add_chunk(p_chunk);
	_asked_chunks[p_chunk->pos()] = false;
	
	for (jgl::Int i = -1; i <= 1; i++)
		for (jgl::Int j = -1; j <= 1; j++)
		{
			jgl::Vector2Int chunk_pos = p_chunk->pos() + jgl::Vector2Int(i, j);
			Chunk* tmp_chunk = Engine::instance()->map()->chunk(chunk_pos);
			if (tmp_chunk != nullptr)
				tmp_chunk->unbake();

		}

	_map_mutex.unlock();
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

jgl::Bool Map_manager::_update()
{
	if (Engine::instance()->player() == nullptr || Engine::instance()->map() == nullptr)
		return (false);

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


void Map_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Chunk_request, SERVER_ACTIVITY{
			Routine::treat_chunk_request_routine(p_client, p_msg);
		});

	Server_manager::server()->add_activity(Server_message::Chunk_modification, SERVER_ACTIVITY{
			Routine::treat_chunk_modification(p_client, p_msg);
		});
}

void Map_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Chunk_data, CLIENT_ACTIVITY{
			Routine::received_chunk_data_routine(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Chunk_modification, CLIENT_ACTIVITY{
			Routine::received_chunk_modification(p_msg);
		});
}

void Map_manager::_initiate()
{
	if (Client_manager::instance() != nullptr)
		_initialize_client();

	if (Server_manager::instance() != nullptr)
		_initialize_server();
}

Map_manager::Map_manager(jgl::Widget* p_parent) : Graphical_widget(p_parent)
{

	_initiate();
}

Map_manager* Map_manager::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Map_manager(p_parent);
		_instance->activate();
	}
	return (_instance);
}

Map_manager* Map_manager::instance()
{
	return (_instance);
}