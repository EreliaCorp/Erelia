#pragma once

#include "jgl.h"

class Entity
{
private:
	jgl::Long _id;
	jgl::Sprite_sheet* _sprite_sheet;
	jgl::Vector2Int _sprite;
	jgl::Vector2 _pos;
	jgl::Vector2Int _size;

	//Movement relative attribut
	jgl::Vector2 _starting_pos;
	jgl::Vector2 _destination;
	jgl::Vector2 _movement;
	jgl::Ulong _move_speed = 100u;
	jgl::Ulong _start_motion_time;

	void _join_destination();
public:
	Entity(jgl::Long p_id);
	void place(jgl::Vector2 p_pos);
	void move(jgl::Vector2 p_delta);

	void set_id(jgl::Long p_id) { _id = p_id; }
	void set_sprite_sheet(jgl::Sprite_sheet* p_sprite_sheet) { _sprite_sheet = p_sprite_sheet; }
	void set_sprite(jgl::Vector2Int p_sprite) { _sprite = p_sprite; }
	void set_move_speed(jgl::Ulong p_move_speed) { _move_speed = p_move_speed; }

	void update();

	jgl::Long id() { return (_id); }
	jgl::Sprite_sheet* sprite_sheet() { return (_sprite_sheet); }
	jgl::Vector2Int sprite() const { return (_sprite); }
	jgl::Vector2 pos() const { return (_pos); }
	jgl::Vector2Int size() const { return (_size); }

	jgl::Bool is_moving() { return (_movement != 0); }
};
