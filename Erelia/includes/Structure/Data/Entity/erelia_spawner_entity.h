#pragma once

#include "jgl.h"
#include "structure/Data/Entity/erelia_entity.h"

class Spawner_entity : public Entity
{
protected:

public:
	Spawner_entity(jgl::String p_name, jgl::Long p_id);

	void save(jgl::File& p_file);
	static Spawner_entity* load(jgl::File& p_file);
};