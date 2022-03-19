#include "erelia.h"

Monster::Monster(jgl::String p_path)
{
	jgl::File file = jgl::open_file(p_path, jgl::File_mode::in);

	_id = jgl::stoi(jgl::get_str(file));
	_name = jgl::get_str(file);
}

Monster* Monster::instanciate()
{
	Monster* result = new Monster(*this);

	return (result);
}

jgl::Array<Monster*> g_monster_array;

void Loading_screen::load_monster()
{
	jgl::Array<jgl::String> file_list = jgl::list_files(Path_atlas::monster_folder_path, Path_atlas::monster_file_extension);

	for (jgl::Size_t i = 0; i < file_list.size(); i++)
	{
		g_monster_array.push_back(new Monster(file_list[i]));
	}
}