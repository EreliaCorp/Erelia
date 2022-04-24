#include "widget/commun/erelia_slider_widget.h"

void Slider::_on_geometry_change()
{

}

void Slider::_render()
{

}

jgl::Bool Slider::_update()
{
	if (_is_in_motion == true)
	{
		jgl::Ulong actual_tick = jgl::Application::active_application()->time() - _starting_time;

		jgl::Vector2 position = jgl::lerp<jgl::Vector2>(_start_position, _final_position, actual_tick, _slide_duration);

		set_geometry(position, _area);

		if (actual_tick >= _slide_duration)
		{
			_is_in_motion = false;
		}
	}
	return (false);
}

Slider::Slider(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

void Slider::set_slide_time(jgl::Ulong p_slide_duration)
{
	_slide_duration = p_slide_duration;
}

void Slider::define_position(jgl::Vector2Int p_closed_position, jgl::Vector2Int p_opened_position)
{
	_closed_position = p_closed_position;
	_opened_position = p_opened_position;
}

void Slider::open()
{
	_is_opened = true;
	_is_in_motion = true;
	_starting_time = jgl::Application::active_application()->time();

	_start_position = _closed_position;
	_final_position = _opened_position;
}
void Slider::close()
{
	if (_is_opened == false || _is_in_motion == true)
		return;

	_is_opened = false;
	_is_in_motion = true;
	_starting_time = jgl::Application::active_application()->time();

	_start_position = _opened_position;
	_final_position = _closed_position;
}

void Slider::change_state()
{
	if (_is_opened == true)
	{
		close();
	}
	else
	{
		open();
	}
}