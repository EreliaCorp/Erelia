#pragma once

#include "jgl.h"

#include "Structure/Atlas/erelia_path_atlas.h"

class UI_configuration_file
{
private:
	static jgl::String _language;
	static jgl::String _username;
	static jgl::String _password;
	static jgl::String _server_address;
	static jgl::Bool _server_mode;

public:
	static void load(jgl::String p_path);
	static void save(jgl::String p_path);

	static void set_language(jgl::String p_language) { _language = p_language; }
	static void set_username(jgl::String p_username) { _username = p_username; }
	static void set_password(jgl::String p_password) { _password = p_password; }
	static void set_server_address(jgl::String p_server_address) { _server_address = p_server_address; }
	static void set_language(jgl::Bool p_server_mode) { _server_mode = p_server_mode; }

	static jgl::String language() { return (Path_atlas::language_folder_path + _language + Path_atlas::language_file_extension); }
	static jgl::String username() { return (_username); }
	static jgl::String password() { return (_password); }
	static jgl::String server_address() { return (_server_address); }
	static jgl::Bool server_mode() { return (_server_mode); }
};