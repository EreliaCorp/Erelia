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

jgl::Vector2Int Console_output::Line::render(jgl::Vector2Int p_size, jgl::Vector2Int p_anchor, jgl::Float p_depth, jgl::Size_t& p_nb_line_to_dodge)
{
	jgl::Vector2Int result = 0;

	for (jgl::Size_t i = 0; i < _parts.size(); i++)
	{
		if (-result.y + _parts[i].size.y > p_size.y)
			return (result);

		if (p_nb_line_to_dodge > 0)
		{
			p_nb_line_to_dodge--;
		}
		else
		{
			result.y -= jgl::draw_text(_parts[i].data, p_anchor + result, text_size, p_depth, 1.0f, jgl::Color::black(), jgl::Color::black()).y;
		}
	}

	return (result);
}

void Console_output::_render()
{
	_box.render();

	jgl::Vector2Int base_pos = _anchor + jgl::Vector2Int(0, _area.y - Line::text_size) + jgl::Vector2Int(_box.border_size() * 2, 0 - (_box.border_size() * 2));
	jgl::Vector2Int pos = base_pos;

	jgl::Vector2Int size = _area - (_box.border_size() * 4);
	jgl::Size_t nb_line_to_dodge = _nb_line_to_dodge;
	for (jgl::Int i = 0; i < _messages.size() && pos.y - _messages[i].size().y > 0; i++)
	{
		if (_messages[i].computed() == false)
		{
			_messages[i].compute(size);
			_total_nb_line += _messages[i].nb_line();
		}
		
		pos.y += _messages[i].render(size - jgl::Vector2Int(0, base_pos.y - pos.y), pos, _depth + 1, nb_line_to_dodge).y;
	}
}

void Console_output::_on_geometry_change()
{
	_total_nb_line = 0;
	_nb_line_to_dodge = 0;
	_box.set_geometry(_anchor, _area, _depth);
	for (jgl::Int i = 0; i < _messages.size(); i++)
	{
		_messages[i].uncompute();
	}
}

jgl::Bool Console_output::_update()
{
	if (is_pointed() == true)
	{
		if (jgl::Application::active_application()->mouse().wheel() != 0)
		{
			THROW_INFORMATION("Using mouse wheel interaction");
			if (jgl::Application::active_application()->mouse().wheel() > 0)
			{
				if (_nb_line_to_dodge < _total_nb_line)
					_nb_line_to_dodge++;
			}
			else if (jgl::Application::active_application()->mouse().wheel() < 0)
			{
				if (_nb_line_to_dodge > 0)
					_nb_line_to_dodge--;
			}
		}
	}
	return (false);
}

Console_output::Console_output(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_box = jgl::Widget_component::Box(this);
	_box.set_color(jgl::Color(125, 125, 125, 125), jgl::Color(95, 95, 95, 125));
	_box.set_border_size(5);

	_total_nb_line = 0;
	_nb_line_to_dodge = 0;
}

void Console_output::add_message(jgl::String p_msg)
{
	_messages.push_front(p_msg);
	if (_nb_line_to_dodge != 0)
		_nb_line_to_dodge++;
}