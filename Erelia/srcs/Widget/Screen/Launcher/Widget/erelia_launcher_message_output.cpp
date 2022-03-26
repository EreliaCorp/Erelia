#include "erelia.h"

namespace Launcher
{
	void Message_output::_on_geometry_change()
	{
		jgl::Vector2 unit = _area / jgl::Vector2(86, 64);

		for (jgl::Size_t i = 0; i < 3; i++)
		{
			_messages_output[i]->set_geometry(jgl::Vector2(45, 1 + 4 * i) * unit, jgl::Vector2(45.5f, 4) * unit);
		}
	}

	void Message_output::_render()
	{

	}

	Message_output::Message_output(jgl::Widget* p_parent) : jgl::Widget(p_parent)
	{
		for (jgl::Size_t i = 0; i < 3; i++)
		{
			_messages_output[i] = new jgl::Text_label("", this);
			_messages_output[i]->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
			_messages_output[i]->label().set_text_color(jgl::Color::red());
			_messages_output[i]->activate();
		}
	}

	void Message_output::set_text(jgl::String p_text_a, jgl::String p_text_b, jgl::String p_text_c)
	{
		_messages_output[0]->label().set_text(p_text_a);
		_messages_output[1]->label().set_text(p_text_b);
		_messages_output[2]->label().set_text(p_text_c);
	}
}