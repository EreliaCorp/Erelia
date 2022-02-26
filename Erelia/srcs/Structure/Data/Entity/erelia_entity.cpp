#include "erelia.h"

Entity::Entity(jgl::Long p_id)
{
	_id = p_id;
	_destination = 0;
	_join_destination();
}

void Entity::place(jgl::Vector2 p_pos)
{
	_pos = p_pos;
	_starting_pos = _pos;
}

void Entity::_join_destination()
{
	_pos = _destination;
	_movement = 0;
}

void Entity::update()
{
	jgl::Ulong time = jgl::Application::active_application()->time();

	_pos = jgl::lerp(_starting_pos, _destination, time - _start_motion_time, _move_speed);
	
	if (_start_motion_time + _move_speed <= jgl::Application::active_application()->time())
	{
		_join_destination();
	}
}

void Entity::move(jgl::Vector2 p_delta)
{
	_starting_pos = _pos;
	_destination = _pos + p_delta;
	_movement = p_delta / _move_speed;
	_start_motion_time = jgl::Application::active_application()->getTime();
}
