#include "structure/Data/Entity/erelia_AI_controlled_entity.h"
#include "structure/Data/Engine/erelia_engine.h"

AI_controlled_entity::AI_controlled_entity(jgl::String p_name, Type p_type, Movement_info::Pattern p_pattern, jgl::Long p_id) : Entity(p_name, p_type, p_id),
_movement_info()
{
	_movement_info.pattern = p_pattern;
}

void AI_controlled_entity::set_movement_info(Movement_info p_movement_info)
{
	_movement_info = p_movement_info;
	place(_movement_info.data.base);
}

void AI_controlled_entity::place(jgl::Vector2 p_pos)
{
	Entity::place(p_pos);
	_movement_info.data.destination = p_pos;
}

void AI_controlled_entity::update()
{
	if (_movement_info.pattern == Movement_info::Pattern::Static)
		return;

	if (is_moving() == false &&
		_movement_info.data.destination == _pos &&
		_movement_info.data.path.size() == 0)
	{
		if (_movement_info.pattern == Movement_info::Pattern::Wander)
		{
			jgl::Vector2 new_destination = _movement_info.data.generate_destination();

			Engine::instance()->map()->find_path(_movement_info.data.path, _pos, new_destination, _movement_info.data.range * 2);
			_movement_info.data.path_index = 0;
		}
	}

	if (_movement_info.data.destination == _pos)
	{
		if (_last_moving == true)
		{
			_movement_info.data.timer.start();
		}
		else if (_movement_info.data.timer.timeout() == true)
		{
			if (_movement_info.data.timer.started() == false)
			{
				_movement_info.data.timer.start();
			}
			else if (_movement_info.data.timer.timeout() == true)
			{
				_movement_info.data.timer.stop();
				if (Engine::instance()->entity_collision(this, _pos + _movement_info.data.path[_movement_info.data.path_index]) == nullptr)
				{
					_movement_info.data.destination = _pos + _movement_info.data.path[_movement_info.data.path_index];
					move(_movement_info.data.path[_movement_info.data.path_index]);
					_movement_info.data.path_index++;
				}
			}
		}
		_last_moving = is_moving();
	}
	if (_movement_info.data.path_index >= _movement_info.data.path.size())
		_movement_info.data.path.clear();	
}