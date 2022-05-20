#pragma once

#include "jgl.h"
#include "structure/Data/Entity/erelia_entity.h"
#include "structure/Data/Entity/erelia_enemy.h"

class Spawner : public Entity
{
protected:
	jgl::Array<Enemy*> _childrens;
	jgl::Size_t _max_children;

public:
	Spawner(jgl::String p_name, jgl::Long p_id);

	void update();

	void save(jgl::File& p_file);
	static Spawner* load(jgl::File& p_file);
};