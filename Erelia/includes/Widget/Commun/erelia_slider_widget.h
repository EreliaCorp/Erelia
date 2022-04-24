#pragma once

#include "jgl.h"

class Slider : public jgl::Widget
{
private:
	jgl::Bool _is_opened = false;
	jgl::Bool _is_in_motion = false;
	jgl::Vector2Int _opened_position = 0;
	jgl::Vector2Int _closed_position = 0;
	jgl::Vector2Int _start_position = 0;
	jgl::Vector2Int _final_position = 0;
	jgl::Ulong _starting_time = 0;
	jgl::Ulong _slide_duration = 150;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

public:
	Slider(jgl::Widget* p_parent);

	jgl::Vector2Int opened_position() { return(_opened_position); }
	jgl::Vector2Int closed_position() { return(_closed_position); }

	jgl::Bool is_opened() { return (_is_opened); }
	jgl::Bool is_in_motion() { return (_is_in_motion); }

	void set_slide_time(jgl::Ulong p_slide_duration);

	void define_position(jgl::Vector2Int p_opened_position, jgl::Vector2Int p_closed_position);
	void open();
	void close();

};
