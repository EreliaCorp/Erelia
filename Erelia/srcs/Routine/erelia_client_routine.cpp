#include "erelia.h"

namespace Routine
{
	void treat_ping_request(Connection* p_client, Message& p_msg)
	{
		p_client->send(p_msg);
	}

	void receive_ping_result(Message& p_msg)
	{
		jgl::Ulong time;
		jgl::Ulong delta_time;

		p_msg >> time;
		delta_time = jgl::Application::active_application()->time() - time;

		Console_manager::instance()->console_output()->add_message("[Syst] - " + jgl::itoa(delta_time) + "ms");
	}

	void client_logout_routine(Connection* p_client)
	{
		Account* tmp_account = Account_atlas::instance()->active_account(p_client->id());
		
		if (tmp_account != nullptr)
		{
			jgl::Long entity_id = tmp_account->id;
			Account_atlas::instance()->desactivate_account(p_client->id());

			static Message msg(Server_message::Entity_suppression);

			msg.clear();

			msg << entity_id;

			Server_manager::server()->send_to_all(msg, p_client);
		}
	}

	void receive_gamemode_change(Message& p_msg)
	{
		Gamemode mode;

		p_msg >> mode;

		Game_screen::instance()->set_gamemode(mode);
	}
}