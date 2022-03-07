#include "erelia.h"

Abstract_console_parser::Command::Command(jgl::String p_text, Connection* p_sender)
{
	text = p_text;
	sender = p_sender;
}

void Abstract_console_parser::_render()
{

}

void Abstract_console_parser::_on_geometry_change()
{

}

jgl::Bool Abstract_console_parser::_update()
{
	if (_command_pool.size() != 0)
	{
		Command head = _command_pool.front();
		_command_pool.pop_front();
		_parse_command(head);
	}
	return (false);
}

void Abstract_console_parser::_send_global_message(jgl::String p_text)
{
	static Message result(Server_message::Console_message);

	result << p_text;

	Server_manager::server()->send_to_all(result);
}

void Abstract_console_parser::_send_gamemode_modification(Connection* p_client, Gamemode p_mode)
{
	static Message result(Server_message::Gamemode_message);

	result << p_mode;

	Server_manager::server()->send_to(p_client, result);
}

void Abstract_console_parser::_send_private_message(jgl::String p_text, Connection* p_client)
{
	static Message result(Server_message::Console_message);

	result << p_text;

	Server_manager::server()->send_to(p_client, result);
}

Abstract_console_parser::Abstract_console_parser(class Console_output* p_output, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_output = p_output;
}

void Abstract_console_parser::add_command(jgl::String p_command, Connection* p_sender)
{
	_command_pool.push_back(Command(p_command, p_sender));
}