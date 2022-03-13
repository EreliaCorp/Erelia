#include "erelia.h"

namespace Routine
{
	void treat_ID_request(Connection* p_client, Message& p_msg)
	{
		jgl::Long id = Engine::instance()->request_id();
		jgl::Vector2 pos = Account_atlas::instance()->active_account(p_client->id())->pos;

		static Message result(Server_message::ID_data);

		result.clear();

		result << id;
		result << pos;

		Entity* new_entity = new Entity(id);
		new_entity->place(pos);

		Account_atlas::instance()->active_account(p_client->id())->id = id;
		

		Engine::instance()->add_entity(new_entity);

		p_client->send(result);
	}

	void receive_player_ID_data(Message& p_msg)
	{
		jgl::Long id;
		jgl::Vector2 pos;

		p_msg >> id;
		p_msg >> pos;

		Engine::instance()->initialize_player(id);
		Engine::instance()->player()->place(pos);

		Main_application::instance()->transition_to_game();
	}
}