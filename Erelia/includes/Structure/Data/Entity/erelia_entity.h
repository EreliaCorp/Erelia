#pragma once

#include "jgl.h"

class Entity
{
private:
	jgl::Vector2 _pos;

public:
	Entity();
	void place(jgl::Vector2 p_pos);
	void move(jgl::Vector2 p_delta);

	jgl::Vector2 pos() const { return (_pos); }
};
