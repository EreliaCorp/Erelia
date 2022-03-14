#include "erelia.h"

namespace Routine
{
	void send_connection_request(jgl::String p_username, jgl::String p_password)
	{
		if (p_username != "" && p_password != "")
		{
			static Message msg(Server_message::Connection_request);

			msg.clear();
			msg << p_username;
			msg << p_password;

			UI_configuration_file::set_username(p_username);
			UI_configuration_file::set_password(p_password);

			Client_manager::client()->send(msg);
		}
	}

	void send_registration_request(jgl::String p_username, jgl::String p_password)
	{
		static Message msg(Server_message::Register_request);

		msg.clear();
		msg << p_username;
		msg << p_password;

		Client_manager::client()->send(msg);
	}

	void treat_connection_request(Connection* p_client, Message& p_msg)
	{
		if (Account_atlas::instance() == nullptr)
			return;

		jgl::String username;
		jgl::String password;

		p_msg >> username;
		p_msg >> password;

		Account* tmp_account = Account_atlas::instance()->account(username);

		static Message result(Server_message::Connection_screen_communication);

		result.clear();
		if (tmp_account == nullptr || tmp_account->password != password)
		{
			result.header.id = Server_message::Connection_screen_communication;
			jgl::String text = "Connection_rejected";
			result << text;

			p_client->send(result);
		}
		else
		{
			if (tmp_account->connection == nullptr)
			{
				result.header.id = Server_message::Connection_accepted;

				tmp_account->connection = p_client;
				Account_atlas::instance()->activate_account(tmp_account);

				p_client->send(result);

				static Message info(Server_message::Console_message);
				info.clear();
				jgl::String info_text = Translation_atlas::string("login_pre_name") + tmp_account->username + Translation_atlas::string("login_post_name");
				info << info_text;
				Server_manager::server()->send_to_all(info, p_client);
			}
			else
			{
				result.header.id = Server_message::Connection_screen_communication;
				jgl::String text = "Already_connected";

				result << text;

				p_client->send(result);
			}
		}
	}

	void treat_registration_request(Connection* p_client, Message& p_msg)
	{
		jgl::String username;
		jgl::String password;

		p_msg >> username;
		p_msg >> password;

		Account* tmp_account = Account_atlas::instance()->account(username);

		static Message result(Server_message::Connection_screen_communication);

		result.clear();
		if (tmp_account != nullptr)
		{
			jgl::String text = "Registration_rejected";
			result << text;

			p_client->send(result);
		}
		else
		{
			Account_atlas::instance()->add_account(username, password);
			result.header.id = Server_message::Connection_screen_communication;

			jgl::String text = "Registration_accepted";
			result << text;

			p_client->send(result);
		}
	}

	void treat_connection_message(Message& p_msg)
	{
		jgl::String text;

		p_msg >> text;

		Connection_screen::instance()->set_text(Translation_atlas::string(text));
	}
}