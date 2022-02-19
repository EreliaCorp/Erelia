#include "erelia.h"

UI_configuration_file::UI_configuration_file()
{

}

const jgl::Array<UI_configuration_file::Server_info>& UI_configuration_file::servers_info()
{
	return (_servers_info);
}

const jgl::String& UI_configuration_file::player_username()
{
	return (_player_username);
}

const jgl::String& UI_configuration_file::player_password()
{
	return (_player_password);
}

void UI_configuration_file::set_player_username(jgl::String p_username)
{
	_player_username = p_username;
}

void UI_configuration_file::set_player_password(jgl::String p_password)
{
	_player_password = p_password;
}

void UI_configuration_file::add_server(UI_configuration_file::Server_info p_new_server)
{
	_servers_info.push_back(p_new_server);
}

void UI_configuration_file::add_server(jgl::String p_server_id, jgl::String p_server_name)
{
	Server_info new_server = Server_info();

	new_server.server_ip = p_server_id;
	new_server.server_name = p_server_name;

	_servers_info.push_back(new_server);
}

void UI_configuration_file::_load_server_info(jgl::File& intput_file)
{
	while (intput_file.peek() != EOF)
	{
		jgl::Array<jgl::String> tab = jgl::get_strsplit(intput_file, ":", 2);

		Server_info tmp_result;
		tmp_result.server_name = tab[0];
		tmp_result.server_ip = tab[1];

		_servers_info.push_back(tmp_result);
	}
}

void UI_configuration_file::_save_server_info(jgl::File& output_file)
{
	for (jgl::Size_t i = 0; i < _servers_info.size(); i++)
	{
		output_file << _servers_info[i].server_name << ":" << _servers_info[i].server_ip << std::endl;
	}
}

void UI_configuration_file::_load_player_server_info(jgl::File& intput_file)
{
	jgl::Array<jgl::String> tab = jgl::get_strsplit(intput_file, ":", 2);

	_player_username = tab[0];
	_player_password = tab[1];
}

void UI_configuration_file::_save_player_server_info(jgl::File& output_file)
{
	output_file << _player_username << ":" << _player_password << std::endl;
}

void UI_configuration_file::load(jgl::String p_file_name)
{
	jgl::File tmp_file = jgl::open_file(Path_atlas::ui_configuration_path + p_file_name, jgl::File_mode::in);

	_load_player_server_info(tmp_file);
	_load_server_info(tmp_file);

	tmp_file.close();
}

void UI_configuration_file::save(jgl::String p_file_name)
{
	jgl::File tmp_file = jgl::open_file(Path_atlas::ui_configuration_path + p_file_name, jgl::File_mode::out);

	jgl::cout << _player_username << ":" << _player_password << jgl::endl;
	
	for (jgl::Size_t i = 0; i < _servers_info.size(); i++)
	{
		jgl::cout << _servers_info[i].server_name << ":" << _servers_info[i].server_ip << jgl::endl;
	}

	_save_player_server_info(tmp_file);
	_save_server_info(tmp_file);

	tmp_file.close();
}
