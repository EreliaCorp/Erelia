#include "erelia.h"

namespace Routine
{
	void treat_chunk_request_routine(Connection* p_client, Message& p_msg)
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

	void received_chunk_data_routine(Message& p_msg)
	{
		while (p_msg.empty() == false)
		{
			jgl::Vector2Int chunk_pos;

			p_msg >> chunk_pos;

			Chunk* result = new Chunk(chunk_pos);
			p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->content()), sizeof(jgl::Short) * Chunk::C_SIZE * Chunk::C_SIZE * Chunk::C_LAYER_LENGTH);
			p_msg.load_from_array(reinterpret_cast<jgl::Uchar*>(result->encounter()), sizeof(jgl::Int) * Chunk::C_SIZE * Chunk::C_SIZE);

			Map_manager::instance()->receive_chunk(result);
		}
	}

	void treat_chunk_modification(Connection* p_client, Message& p_msg)
	{
		Server_manager::server()->send_to_all(p_msg, p_client);
	}

	void received_chunk_modification(Message& p_msg)
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
}