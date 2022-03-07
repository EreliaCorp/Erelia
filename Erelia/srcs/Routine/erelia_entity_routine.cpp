#include "erelia.h"

namespace Routine
{
	void treat_player_motion(Connection* p_client, Message& p_msg)
	{
		jgl::Long id;
		jgl::Vector2Int delta;

		p_msg >> id;
		p_msg >> delta;

		if (true)
		{
			Entity* tmp_entity = Engine::instance()->entity(id);
		
			if (tmp_entity != nullptr && tmp_entity->is_moving() == false)
			{
				tmp_entity->move(delta);
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