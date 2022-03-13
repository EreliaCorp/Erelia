#include "erelia.h"

Debug_screen* Debug_screen::_instance = nullptr;

Debug_screen* Debug_screen::instanciate(jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Debug_screen(p_parent);
		_instance->activate();
	}
	return (_instance);
}

void Debug_screen::set_text(jgl::Size_t line, jgl::Size_t row, jgl::String p_text)
{
	_lines[row][line]->set_text(p_text);
}

void Debug_screen::_render()
{
	for (jgl::Size_t j = 0; j < 3; j++)
	{
		for (jgl::Size_t i = 0; i < 30; i++)
		{
			_lines[j][i]->render();
		}
	}
}
	
void Debug_screen::_on_geometry_change()
{
	jgl::Vector2Int label_size = _area / jgl::Vector2Int(3, 31);

	for (jgl::Size_t j = 0; j < 3; j++)
	{
		for (jgl::Size_t i = 0; i < 30; i++)
		{
			_lines[j][i]->set_geometry(label_size * jgl::Vector2Int(j, i) + label_size.y / 2, label_size, _depth);
		}
	}
}

jgl::Bool Debug_screen::_update()
{
	static jgl::Timer message_timer(4);
	static jgl::Size_t old_value = 15;
	
	if (old_value != Client_manager::client()->input().size() && message_timer.timeout())
	{
		old_value = Client_manager::client()->input().size();
		_lines[0][0]->set_text("Nb message : " + jgl::itoa(old_value));
		message_timer.start();
	}

	_lines[0][1]->set_text("Render FPS : " + jgl::itoa(jgl::Application::active_application()->fps_render()));
	_lines[0][2]->set_text("Update FPS : " + jgl::itoa(jgl::Application::active_application()->fps_update()));

	return (false);
}

jgl::Bool Debug_screen::_fixed_update()
{
	return (false);
}
	
Debug_screen::Debug_screen(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	for (jgl::Size_t j = 0; j < 3; j++)
	{
		for (jgl::Size_t i = 0; i < 30; i++)
		{
			_lines[j][i] = new jgl::Widget_component::Text_label("", this);
			_lines[j][i]->set_horizontal_align(jgl::Horizontal_alignment::Left);
			_lines[j][i]->set_vertical_align(jgl::Vertical_alignment::Centred);
			_lines[j][i]->set_text_color(jgl::Color::white());
		}
	}
}
	