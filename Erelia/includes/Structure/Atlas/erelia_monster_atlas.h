#pragma once

#include "structure/Data/Monster/erelia_monster.h"

class Monster_atlas
{
private:
	Monster_atlas();

	jgl::Array<Monster*> _monster_array;

	void _load();

	static Monster_atlas* _instance;
public:
	Monster* monster(jgl::Size_t p_index);

	static Monster_atlas* instanciate();
	static Monster_atlas* instance() { return (_instance); }
};