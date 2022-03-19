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