#pragma once

#include "jgl.h"

#include "Structure/Data/Map/erelia_map.h"

class Engine
{
private:
	static Engine* _instance;

	Player* _player;

	Engine();

public:
	Player* player() { return (_player); }

	void load_map(jgl::String p_world_path);

	static Engine* instanciate();

	static Engine* instance();
};