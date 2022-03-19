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

				if (tmp_value != -1 && tmp_value < Engine::instance()->encounter_areas().size())
				{
					Battle_room* tmp_room = Battle_manager::instance()->generate_battle_room(Engine::instance()->encounter_area(tmp_value));
					if (tmp_room != nullptr)
					{
						tmp_room->add_monster(Battle_room::Team::Blue, Battle_room::Slot::SlotA, Account_atlas::instance()->active_account(p_client->id())->monsters[0]);
						delete tmp_room;
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