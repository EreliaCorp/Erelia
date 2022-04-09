#include "structure/Data/Entity/erelia_NPC.h"
#include "structure/Data/Engine/erelia_engine.h"

NPC::NPC(Entity::Type p_type) : Entity(p_type, -1)
{

}

void NPC::place(jgl::Vector2 p_pos)
{
	Entity::place(p_pos);
	_movement_info.data.destination = p_pos;
}

void NPC::update()
{
	if (_movement_info.pattern == NPC::Movement_info::Pattern::Static)
		return;

	if (_movement_info.data.destination == _pos)
	{
		if (_movement_info.pattern == NPC::Movement_info::Pattern::Wondering)
		{
			jgl::Vector2 new_destination = _movement_info.data.calc_destination();
			
			Engine::instance()->map()->find_path(_movement_info.data.path, _pos, new_destination, _movement_info.data.range * 2);
		}
	}
}