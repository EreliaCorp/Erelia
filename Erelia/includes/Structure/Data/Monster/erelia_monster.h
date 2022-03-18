#pragma once

#include "jgl.h"

class Monster
{
private:
	jgl::Uint id;

public:
	Monster(jgl::Uint p_id)
	{
		id = p_id;
	}
};