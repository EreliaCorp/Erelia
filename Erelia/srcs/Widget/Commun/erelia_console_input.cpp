#include "erelia.h"

void Console_input::_render()
{

}

void Console_input::_on_geometry_change()
{
	_text_entry->set_geometry(0, _area);
}

jgl::Bool Console_input::_update()
{
	if (_text_entry->is_selected() == true)
	{
		if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Up_arrow) == jgl::Input_status::Release && _old_line_index > 0)
		{
			_old_line_index--;
			_text_entry->set_text(_old_line[_old_line_index]);
		}
		else if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Down_arrow) == jgl::Input_status::Release && _old_line_index < _old_line.size())
		{
			_old_line_index++;
			if (_old_line_index < _old_line.size())
				_text_entry->set_text(_old_line[_old_line_index]);
			else
				_text_entry->set_text("");
		}
	}
	return (false);
}

Console_input::Console_input(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_text_entry = new jgl::Text_entry("", this);
	_text_entry->label().set_text_color(jgl::Color::black());
	_text_entry->box().set_color(jgl::Color(125, 125, 125, 125), jgl::Color(95, 95, 95, 125));
	_text_entry->box().set_border_size(5);
	_text_entry->activate();
}