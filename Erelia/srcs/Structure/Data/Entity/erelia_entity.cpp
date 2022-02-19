#include "erelia.h"

Entity::Entity()
{
	_pos = 0;
}

void Entity::place(jgl::Vector2 p_pos)
{
	_pos = p_pos;
}

void Entity::move(jgl::Vector2 p_delta)
{
	_pos += p_delta;
}
