#include "erelia.h"

namespace Routine
{
	void treat_ping_request(Connection* p_client, Message& p_msg)
	{
		jgl::cout << "Server - Treating ping message" << jgl::endl;
		p_client->send(p_msg);
	}

	void receive_ping_result(Message& p_msg)
	{
		jgl::Ulong time;
		jgl::Ulong delta_time;

		jgl::cout << "Client - Treating ping message" << jgl::endl;

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

			static Message msg2(Server_message::Console_message);

			msg2.clear();

			jgl::String msg_text = Translation_atlas::string("logout_pre_name") + tmp_account->username + Translation_atlas::string("logout_post_name");

			msg2 << msg_text;

			Server_manager::server()->send_to_all(msg2, p_client);
		}
	}

	void receive_gamemode_change(Message& p_msg)
	{
		Gamemode mode;

		p_msg >> mode;

		Game_screen::instance()->set_gamemode(mode);
	}

	void receive_brush_size_change(Message& p_msg)
	{
		jgl::Uchar value;

		p_msg >> value;

		Player_manager::instance()->player_interacter()->set_brush_radius(value);
	}

	void receive_brush_type_change(Message& p_msg)
	{
		Player_interacter::Brush_type value;

		p_msg >> value;

		Player_manager::instance()->player_interacter()->set_brush_type(value);
	}

	void receive_brush_type_data_change(Message& p_msg)
	{
		jgl::String value;

		p_msg >> value;

		Player_manager::instance()->player_interacter()->set_brush_type_info(value);
	}
}