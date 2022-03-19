#pragma once

#include "jgl.h"

class Monster
{
private:
	jgl::Uint _id;
	jgl::String _name;

public:
	Monster(jgl::String p_path);

	Monster* instanciate();
};

extern jgl::Array<Monster*> g_monster_array;