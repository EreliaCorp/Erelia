#pragma once

#include "jgl.h"

class UI_configuration_file
{
public:
	struct Server_info
	{
		jgl::String server_ip = "";
		jgl::String server_name = "";
	};
private:
	jgl::Array<Server_info> _servers_info;
	jgl::String _player_username;
	jgl::String _player_password;

	void _load_server_info(jgl::File& intput_file);
	void _save_server_info(jgl::File& output_file);

	void _load_player_server_info(jgl::File& input_file);
	void _save_player_server_info(jgl::File& input_file);

public:
	UI_configuration_file();

	const jgl::Array<Server_info>& servers_info();
	const jgl::String& player_username();
	const jgl::String& player_password();

	void set_player_username(jgl::String p_username);
	void set_player_password(jgl::String p_password);

	void add_server(Server_info p_new_server);
	void add_server(jgl::String p_server_id, jgl::String p_server_name);

	void load(jgl::String p_file_name);
	void save(jgl::String p_file_name);
};
