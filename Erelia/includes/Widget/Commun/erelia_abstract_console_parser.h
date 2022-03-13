#pragma once

#include "jgl.h"

#include "network/erelia_network_definition.h"

class Abstract_console_parser : public jgl::Widget
{
public:
	struct Command
	{
		jgl::String text;
		Connection* sender;

		Command(jgl::String p_text, Connection* p_sender);
	};

protected:

	std::deque<Command> _command_pool;
	class Console_output* _output;

	void _render();

	void _on_geometry_change();

	jgl::Bool _update();

	virtual void _parse_command(Command& p_command) = 0;

	void _send_brush_size_modification(Connection* p_client, jgl::Uchar p_value);
	void _send_gamemode_modification(Connection* p_client, Gamemode p_mode);
	void _send_brush_type_modification(Connection* p_client, Player_interacter::Brush_type p_type);
	void _send_brush_type_data(Connection* p_client, jgl::String p_data);

public:
	Abstract_console_parser(class Console_output* p_output, jgl::Widget* p_parent);

	void add_command(jgl::String p_command, Connection* p_sender);

	void send_global_message(jgl::String p_text);
	void send_private_message(jgl::String p_text, Connection* p_client);
};