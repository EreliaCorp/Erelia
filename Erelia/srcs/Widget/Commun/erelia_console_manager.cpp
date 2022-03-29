#include "Widget/Commun/erelia_console_manager.h"

void Console_manager::_on_geometry_change()
{
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 5 * 2, _area.y / 3);
	jgl::Vector2Int entry_size = jgl::Vector2Int(frame_size.x, frame_size.y / 8);
	if (entry_size.y < 35)
		entry_size.y = 35;

	if (_console_output != nullptr)
		_console_output->set_geometry(jgl::Vector2Int(0, _area.y - entry_size.y - frame_size.y), frame_size);
	if (_console_input != nullptr)
		_console_input->set_geometry(jgl::Vector2Int(0, _area.y - entry_size.y), entry_size);
	if (_console_parser != nullptr)
		_console_parser->set_geometry(0, _area);
}

void Console_manager::_render()
{

}

void Console_manager::_send_command()
{
	Message msg(Server_message::Command_input);

	msg << _console_input->text();

	Client_manager::client()->send(msg);

	_console_input->reset_text();
}

jgl::Bool Console_manager::_update()
{
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Return) == jgl::Input_status::Release)
	{
		if (_console_input->is_selected() == true)
		{
			_send_command();
		}
		else
		{
			_console_input->text_entry()->select();
		}
	}

	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Escape) == jgl::Input_status::Release && _console_input->is_selected() == true)
		_console_input->text_entry()->unselect();

	return (false);
}

Console_manager::Console_manager(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_console_output = new Console_output(this);
	_console_output->set_depth(_depth + 100);
	_console_output->activate();

	_console_input = new Console_input(this);
	_console_input->set_depth(_depth + 100);
	_console_input->activate();

	_console_parser = new Console_parser(_console_output, this);
	_console_parser->set_depth(_depth + 100);
	_console_parser->activate();

	_initiate();
}

void Console_manager::_treat_command_input(Connection* p_client, Message& p_msg)
{
	jgl::String message;

	p_msg >> message;

	Console_manager::instance()->console_parser()->add_command(message, p_client);
}

void Console_manager::_receive_console_message(Message& p_msg)
{
	jgl::String message;

	p_msg >> message;

	Console_manager::instance()->console_output()->add_message(message);
}

void Console_manager::_treat_ping_request(Connection* p_client, Message& p_msg)
{
	p_client->send(p_msg);
}

void Console_manager::_receive_ping_result(Message& p_msg)
{
	jgl::Ulong time;
	jgl::Ulong delta_time;

	p_msg >> time;
	delta_time = jgl::Application::active_application()->time() - time;

	Console_manager::instance()->console_output()->add_message("[Syst] - Ping : " + jgl::itoa(delta_time) + "ms");
}

void Console_manager::send_global_message(jgl::String p_text)
{
	static Message result(Server_message::Console_message);

	result.clear();

	result << p_text;

	Server_manager::server()->send_to_all(result);
}

void Console_manager::send_private_message(jgl::String p_text, Connection* p_client)
{
	static Message result(Server_message::Console_message);

	result.clear();

	result << p_text;

	Server_manager::server()->send_to(p_client, result);
}

void Console_manager::_initialize_server()
{
	Server_manager::server()->add_activity(Server_message::Command_input, SERVER_ACTIVITY{
			_treat_command_input(p_client, p_msg);
		});
	Server_manager::server()->add_activity(Server_message::Ping, SERVER_ACTIVITY{
			_treat_ping_request(p_client, p_msg);
		});
}

void Console_manager::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Console_message, CLIENT_ACTIVITY{
			_receive_console_message(p_msg);
		});
	Client_manager::client()->add_activity(Server_message::Ping, CLIENT_ACTIVITY{
			_receive_ping_result(p_msg);
		});
}