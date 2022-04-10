#include "structure/Data/Entity/erelia_NPC.h"
#include "structure/Data/Engine/erelia_engine.h"

NPC::NPC(jgl::String p_name, jgl::Long p_id) : Entity(p_name, Entity::Type::NPC, p_id)
{

}

void NPC::place(jgl::Vector2 p_pos)
{
	Entity::place(p_pos);
	_movement_info.data.destination = p_pos;
}

void NPC::update()
{
	jgl::cout << "Static NPC [" << _id << "]" << jgl::endl;
	if (_movement_info.pattern == NPC::Movement_info::Pattern::Static)
		return;

	jgl::cout << "Update NPC not wondering [" << _id << "]" << jgl::endl;
	if (_movement_info.data.destination == _pos && _movement_info.data.path.size() == 0)
	{
		if (_movement_info.pattern == NPC::Movement_info::Pattern::Wondering)
		{
			jgl::Vector2 new_destination = _movement_info.data.generate_destination();
			
			Engine::instance()->map()->find_path(_movement_info.data.path, _pos, new_destination, _movement_info.data.range * 2);

			jgl::cout << "Entity [" << _id << "] path : " << _movement_info.data.path << jgl::endl;
		}
	}
}