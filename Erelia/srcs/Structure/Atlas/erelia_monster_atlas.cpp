#include "Structure/Atlas/erelia_monster_atlas.h"
#include "Structure/Atlas/erelia_path_atlas.h"

Monster_atlas::Monster_atlas()
{
	_load();
}

void Monster_atlas::_load()
{
	jgl::Array<jgl::String> file_list = jgl::list_files(Path_atlas::monster_folder_path, Path_atlas::monster_file_extension);

	for (jgl::Size_t i = 0; i < file_list.size(); i++)
	{
		_monster_array.push_back(new Monster(file_list[i]));
	}
}

Monster* Monster_atlas::monster(jgl::Size_t p_index)
{
	if (p_index >= _monster_array.size())
		return (nullptr);
	return (_monster_array[p_index]);
}