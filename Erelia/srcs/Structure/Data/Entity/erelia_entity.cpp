#include "Structure/Data/Entity/erelia_entity.h"

Entity::Entity(jgl::String p_name, Type p_type, jgl::Long p_id)
{
	_name = p_name;
	_type = p_type;
	_sprite_sheet = nullptr;
	_sprite = 0;
	_id = p_id;
	_size = 1;
	_destination = 0;
	_move_speed = 100u;
	_is_moving = false;
	_join_destination();
}

void Entity::place(jgl::Vector2 p_pos)
{
	_pos = p_pos;
	_starting_pos = _pos;
	_destination = _pos;
}

void Entity::_join_destination()
{
	_pos = _destination.round();
}

void Entity::update()
{

}

void Entity::update_pos()
{
	jgl::Ulong time = jgl::Application::active_application()->time();

	_pos = jgl::lerp(_starting_pos, _destination, time - _start_motion_time, _move_speed);

	if (_start_motion_time + _move_speed <= jgl::Application::active_application()->time())
	{
		_join_destination();
		_is_moving = false;
	}
}

void Entity::move(jgl::Vector2 p_delta)
{
	_starting_pos = _pos;
	_movement = p_delta;
	_destination = _pos + p_delta;
	_start_motion_time = jgl::Application::active_application()->time();
	_is_moving = true;
}
