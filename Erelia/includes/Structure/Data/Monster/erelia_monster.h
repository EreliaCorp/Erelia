#pragma once

#include "jgl.h"

class Monster
{
private:
	jgl::Uint _id;
	jgl::String _name;
	jgl::Size_t _level;

public:
	Monster(jgl::String p_path);

	Monster* instanciate();

	void set_id(jgl::Uint p_id) { _id = p_id; }
	void set_name(jgl::String p_name) { _name = p_name; }
	void set_level(jgl::Size_t p_level) { _level = p_level; }

	const jgl::Uint id() const { return (_id); }
	const jgl::String name() const { return (_name); }
	const jgl::Size_t level() const { return (_level); }
};