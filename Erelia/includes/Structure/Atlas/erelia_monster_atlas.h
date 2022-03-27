#pragma once

#include "structure/Data/Monster/erelia_monster.h"

class Monster_atlas : public jgl::Singleton<Monster_atlas>
{
	friend class jgl::Singleton<Monster_atlas>;
private:
	Monster_atlas();

	jgl::Array<Monster*> _monster_array;

	void _load();

public:
	Monster* monster(jgl::Size_t p_index);
};