#include "erelia.h"

jgl::String UI_configuration_file::_language = "english";
jgl::String UI_configuration_file::_username = "";
jgl::String UI_configuration_file::_password = "";
jgl::String UI_configuration_file::_server_address = "localhost";
jgl::Bool UI_configuration_file::_server_mode = false;

void UI_configuration_file::load(jgl::String p_path)
{
	if (jgl::check_file_exist(p_path) == true)
	{
		jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

		jgl::Array<jgl::String> tab = jgl::get_strsplit(file, ":", -1);
		_language = (tab.size() == 2 ? tab[1] : "");

		tab = jgl::get_strsplit(file, ":", -1);
		_username = (tab.size() == 2 ? tab[1] : "");

		tab = jgl::get_strsplit(file, ":", -1);
		_password = (tab.size() == 2 ? tab[1] : "");

		tab = jgl::get_strsplit(file, ":", -1);
		_server_address = (tab.size() == 2 ? tab[1] : "");

		tab = jgl::get_strsplit(file, ":", -1);
		_server_mode = (tab.size() == 2 && tab[1] == "on" ? true : false);

		file.close();
	}
}

void UI_configuration_file::save(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::out);

	file << "Language:" << _language << std::endl;
	file << "Username:" << _username << std::endl;
	file << "Password:" << _password << std::endl;
	file << "Address:" << _server_address << std::endl;
	file << "Server_mode:" << (_server_mode == true ? "on" : "off") << std::endl;

	file.close();
}
