#include "erelia.h"

namespace Routine
{
	void treat_ID_request(Connection* p_client, Message& p_msg)
	{
		jgl::Long id = Engine::instance()->request_id();

		static Message result(Server_message::ID_data);

		result.clear();

		result << id;

		Entity* new_entity = new Entity(id);

		Account_atlas::instance()->active_account(p_client->id())->id = id;

		Engine::instance()->add_entity(new_entity);

		p_client->send(result);
	}

	void receive_player_ID_data(Message& p_msg)
	{
		jgl::Long id;

		p_msg >> id;

		Engine::instance()->initialize_player(id);

		Main_application::instance()->transition_to_game();
	}
}