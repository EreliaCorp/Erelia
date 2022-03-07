#include "erelia.h"

jgl::Map<jgl::String, jgl::String> Translation_atlas::_strings;

void Translation_atlas::load(jgl::String p_path)
{
	if (jgl::check_file_exist(p_path) == false)
	{
		load(Path_atlas::default_language_file);
	}
	else
	{
		_strings.clear();
		jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

		while (file.peek() != EOF)
		{
			jgl::Array<jgl::String> tab = jgl::get_strsplit(file, ";", 2);

			_strings[tab[0]] = tab[1];
		}
	}
}

jgl::String Translation_atlas::string(jgl::String p_key)
{
	if (_strings.count(p_key) == 0)
		return (p_key);
	return (_strings[p_key]);
}