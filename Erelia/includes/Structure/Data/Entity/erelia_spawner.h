#pragma once

#include "jgl.h"
#include "structure/Data/Entity/erelia_entity.h"

class Spawner : public Entity
{
protected:

public:
	Spawner(jgl::String p_name, jgl::Long p_id);

	void update();

	void save(jgl::File& p_file);
	static Spawner* load(jgl::File& p_file);
};