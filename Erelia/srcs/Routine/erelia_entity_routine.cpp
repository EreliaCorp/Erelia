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

				jgl::Vector2Int pos = jgl::Vector2Int(tmp_entity->pos().x + result.x, tmp_entity->pos().y + result.y);

				jgl::Int tmp_value = Engine::instance()->map()->encounter(pos);

				if (tmp_value != -1)
				{
					Encounter_area* tmp_area = Engine::instance()->encounter_area(tmp_value);
					jgl::Uint monster_id = tmp_area->monster(static_cast<jgl::Float>(jgl::generate_nbr(0, 10000)) / 100.0f);
					jgl::cout << "Encounter mob : " << monster_id << jgl::endl;

					if (monster_id != 0)
					{
						Message msg(Server_message::Battle_start_notification);

						msg << monster_id;

						p_client->send(msg);
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