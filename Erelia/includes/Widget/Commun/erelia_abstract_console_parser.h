#pragma once

#include "jgl.h"

#include "network/erelia_network_definition.h"
#include "Widget/Screen/Game_world/erelia_game_world_screen.h"

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

	void _send_ping_request(Connection* p_client);
	void _send_brush_size_modification(Connection* p_client, jgl::Uchar p_value);
	void _send_gamemode_modification(Connection* p_client, Game_world_screen::Event p_mode);
	void _send_brush_type_modification(Connection* p_client, Player_interacter::Brush_type p_type);
	void _send_brush_type_data(Connection* p_client, jgl::String p_data);
	void _send_monster_area_value(Connection* p_client, jgl::Int p_area_value);

public:
	Abstract_console_parser(class Console_output* p_output, jgl::Widget* p_parent);

	void add_command(jgl::String p_command, Connection* p_sender);
};