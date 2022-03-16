#include "erelia.h"

namespace Routine
{
	void treat_player_motion(Connection* p_client, Message& p_msg)
	{
		jgl::Long id;
		jgl::Vector2Int delta;

		p_msg >> id;
		p_msg >> delta;

		Entity* tmp_entity = Engine::instance()->entity(id);

		if (tmp_entity != nullptr && tmp_entity->is_moving() == false)
		{
			jgl::Vector2Int result = 0;
		
			jgl::Vector2Int delta_value[2] = { jgl::Vector2Int(1, 0), jgl::Vector2Int(0, 1) };

			for (jgl::Size_t i = 0; i < 2; i++)
			{
				if (Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), delta * delta_value[i]) == true)
				{
					result += delta * delta_value[i];
				}
			}

			if (result != delta || Engine::instance()->map()->can_move(tmp_entity, tmp_entity->pos(), delta) == true)
			{
				tmp_entity->move(result);

				jgl::Vector3Int pos = jgl::Vector3Int(tmp_entity->pos().x + result.x, tmp_entity->pos().y + result.y, 0);

				for (jgl::Size_t i = 0; i < Chunk::C_LAYER_LENGTH; i++)
				{
					jgl::Short tmp_value = Engine::instance()->map()->content(pos + jgl::Vector3Int(0, 0, i));

					if (tmp_value != -1 && (g_node_array[tmp_value]->obstacle & Node::BUSH) == Node::BUSH)
					{
						i = Chunk::C_LAYER_LENGTH;
						jgl::cout << "Walking in bush" << jgl::endl;
					}
				}
			}

		}
	}

	void receive_entity_data(Message& p_msg)
	{
		if (Server_manager::instance() == nullptr)
		{
			while (p_msg.empty() == false)
			{
				Entity_manager::instance()->receive_entity_data(p_msg);
			}
		}
	}

	void receive_entity_suppression_command(Message& p_msg)
	{
		jgl::Long id;

		p_msg >> id;

		Engine::instance()->remove_entity(id);
	}
}