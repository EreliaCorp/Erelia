#include "erelia.h"

void Console_input::_render()
{

}

void Console_input::_on_geometry_change()
{
	_text_entry->set_geometry(0, _area);
}

Console_input::Console_input(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_text_entry = new jgl::Text_entry("", this);
	_text_entry->box().set_color(jgl::Color(125, 125, 125, 125), jgl::Color(95, 95, 95, 125));
	_text_entry->box().set_border_size(5);
	_text_entry->activate();
}