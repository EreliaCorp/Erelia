#include "Widget/Commun/erelia_console_output.h"

void Console_output::_render()
{
	_box.render();
	for (jgl::Size_t i = 0; i < _messages.size(); i++)
	{
		_messages[i].render();
	}
}

jgl::Size_t Console_output::_compute_text(jgl::String& p_text, jgl::Size_t& p_line_index)
{
	static jgl::Array<jgl::String> tab;
	static jgl::Array<jgl::String> result_tab;
	jgl::Vector2Int pos = 0;

	jgl::String text = "";

	result_tab.clear();
	p_text.split(tab, " ", true);

	for (jgl::Size_t i = 0; i < tab.size(); i++)
	{
		jgl::Vector2Int size = jgl::Application::active_application()->default_font()->calc_text_size(text + tab[i], _text_size);

		if (size.x > _messages[p_line_index].area().x)
		{
			result_tab.push_back(text);
			text = "";
		}
		if (text != "")
			text += " ";
		text += tab[i];
	}
	if (text != "")
		result_tab.push_back(text);


	for (jgl::Size_t i = 0; i < result_tab.size(); i++)
	{
		_messages[p_line_index + result_tab.size() - i - 1].set_text(result_tab[i]);
	}
	return (result_tab.size());
}

void Console_output::_set_output_text()
{
	for (jgl::Size_t i = 0; i < _messages.size() && _message_content.size() > i + _nb_line_to_dodge;)
	{
		i += _compute_text(_message_content[i + _nb_line_to_dodge], i);
	}
}

void Console_output::_on_geometry_change()
{
	_total_nb_line = 0;
	_nb_line_to_dodge = 0;
	_box.set_geometry(_anchor, _area, _depth);
	jgl::Size_t nb_line = (_area.y - _box.border_size() * 2) / _text_size;
	_messages.resize(nb_line);

	jgl::Vector2Int size = jgl::Vector2Int(_area.x - _box.border_size() * 2, (_area.y - _box.border_size() * 2) / nb_line);
	jgl::Vector2Int pos = jgl::Vector2Int(_box.border_size(), _area.y - _box.border_size() * 2 - size.y);

	for (jgl::Size_t i = 0; i < nb_line; i++)
	{
		_messages[i] = jgl::Widget_component::Text_label("", this);
		_messages[i].set_geometry(_anchor + pos, size, _depth + 1);
		pos.y -= size.y;
	}
}

jgl::Bool Console_output::_update()
{
	if (is_pointed() == true)
	{

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
	_message_content.push_front(p_msg);
	if (_nb_line_to_dodge != 0)
		_nb_line_to_dodge++;
	_set_output_text();
}