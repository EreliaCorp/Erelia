#pragma once

#include "structure/Data/Entity/erelia_AI_controlled_entity.h"

class Enemy : public AI_controlled_entity
{
private:
	class Spawner* _owner;

public:
	Enemy(class Spawner* p_owner, jgl::String p_name, jgl::Long p_id);

	void update();
};