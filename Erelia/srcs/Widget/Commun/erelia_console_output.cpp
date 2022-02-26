#include "erelia.h"

jgl::Size_t Console_output::Line::text_size = 20u;

Console_output::Line::Line(jgl::String p_text)
{
	_text = p_text;
	_size = 0;
	_computed = false;
}

void Console_output::Line::compute(jgl::Vector2Int p_area)
{
	static jgl::Array<jgl::String> tab;

	_text.split(tab, " ", true);
	jgl::Vector2Int pos = 0;
	_parts.clear();
	_parts.push_front(Line_value(""));

	for (jgl::Size_t i = 0; i < tab.size(); i++)
	{
		jgl::Vector2Int size = jgl::Application::active_application()->default_font()->calc_text_size(tab[i] + " ", text_size);

		if (pos.x + size.x > p_area.x)
		{
			_parts.front().size = jgl::Vector2Int(pos.x, text_size);
			_parts.push_front(Line_value(""));
			pos.x = size.x;
		}
		else
		{
			pos.x += size.x;
		}
		_parts.front().data += tab[i] + " ";
	}
	_parts.front().size = jgl::Vector2Int(pos.x, text_size);
	_size = jgl::Vector2Int(p_area.x, pos.y + text_size);
}

jgl::Vector2Int Console_output::Line::render(jgl::Vector2Int p_size, jgl::Vector2Int p_anchor, jgl::Float p_depth)
{
	jgl::Vector2Int result = 0;

	for (jgl::Size_t i = 0; i < _parts.size(); i++)
	{
		if (-result.y + _parts[i].size.y > p_size.y)
			return (result);
		
		result.y -= jgl::draw_text(_parts[i].data, p_anchor + result, text_size, p_depth, 1.0f, jgl::Color::black(), jgl::Color::black()).y;
	}

	return (result);
}

void Console_output::_render()
{
	jgl::Vector2Int base_pos = _anchor + jgl::Vector2Int(0, _area.y - Line::text_size) + jgl::Vector2Int(_frame->box().border_size(), 0 - (_frame->box().border_size()));
	jgl::Vector2Int pos = base_pos;

	jgl::Vector2Int size = _area - (_frame->box().border_size() * 2);
	for (jgl::Int i = 0; i < _messages.size() && pos.y - _messages[i].size().y > 0 ; i++)
	{
		if (_messages[i].computed() == false)
			_messages[i].compute(size);

		pos.y += _messages[i].render(size - jgl::Vector2Int(0, base_pos.y - pos.y), pos, _depth + 2).y;
	}
}

void Console_output::_on_geometry_change()
{
	_frame->set_geometry(0, _area);
	for (jgl::Int i = 0; i < _messages.size(); i++)
	{
		_messages[i].uncompute();
	}
}

Console_output::Console_output(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_frame = new jgl::Frame(this);
	_frame->box().set_color(jgl::Color(125, 125, 125, 125), jgl::Color(95, 95, 95, 125));
	_frame->box().set_border_size(5);
	_frame->activate();
}

void Console_output::add_message(jgl::String p_msg)
{
	_messages.push_front(p_msg);
}