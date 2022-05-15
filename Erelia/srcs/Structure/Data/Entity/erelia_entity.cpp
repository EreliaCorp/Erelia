#include "Structure/Data/Entity/erelia_entity.h"

Entity::Entity(jgl::String p_name, Type p_type, jgl::Long p_id)
{
	_name = p_name;
	_type = p_type;
	_sprite_sheet = nullptr;
	_sprite = 0;
	_id = p_id;
	_destination = 0;
	_move_speed = 100u;
	_is_moving = false;
	_join_destination();
}

void Entity::render(jgl::Vector2Int p_anchor, jgl::Vector2Int p_size, jgl::Float p_depth)
{
	if (sprite_sheet() != nullptr)
		sprite_sheet()->draw(sprite(), p_anchor, p_size, p_depth, 1.0f);
	else
	{
		if (type() == Entity::Type::Player)
			jgl::draw_rectangle_color(jgl::Color::blue(), p_anchor, p_size, p_depth);
		else if (type() == Entity::Type::NPC)
			jgl::draw_rectangle_color(jgl::Color::green(), p_anchor, p_size, p_depth);
		else if (type() == Entity::Type::Spawner)
			jgl::draw_rectangle_color(jgl::Color::black(), p_anchor, p_size, p_depth);
		else if (type() == Entity::Type::Enemy)
			jgl::draw_rectangle_color(jgl::Color::red(), p_anchor, p_size, p_depth);
	}
}

void Entity::render_name(jgl::Vector2Int p_anchor, jgl::Float p_depth)
{
	if (type() == Entity::Type::Player)
		jgl::draw_text(name(), p_anchor - jgl::Vector2Int(0, 30), 25, p_depth + 10, 1.0f, jgl::Color::blue(), jgl::Color::black());
	else if (type() == Entity::Type::NPC)
		jgl::draw_text(name(), p_anchor - jgl::Vector2Int(0, 30), 25, p_depth + 10, 1.0f, jgl::Color::green(), jgl::Color::black());
	else if (type() == Entity::Type::Spawner)
		jgl::draw_text(name(), p_anchor - jgl::Vector2Int(0, 30), 25, p_depth + 10, 1.0f, jgl::Color::black(), jgl::Color::black());
	else if (type() == Entity::Type::Enemy)
		jgl::draw_text(name(), p_anchor - jgl::Vector2Int(0, 30), 25, p_depth + 10, 1.0f, jgl::Color::red(), jgl::Color::black());
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
