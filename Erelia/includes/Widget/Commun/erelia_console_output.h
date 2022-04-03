#pragma once

#include "jgl.h"

class Console_output : public jgl::Widget
{
private:
	static const jgl::Size_t _text_size = 20u;
	jgl::Widget_component::Box _box;
	std::deque<jgl::String> _message_content;
	std::deque<jgl::Widget_component::Text_label> _messages;
	jgl::Size_t _total_nb_line;
	jgl::Size_t _nb_line_to_dodge;

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();

	jgl::Size_t _compute_text(jgl::String& p_text, jgl::Size_t& p_line_index);
	void _set_output_text();

public:
	Console_output(jgl::Widget* p_parent);
	void add_message(jgl::String p_msg);
	std::deque<jgl::Widget_component::Text_label>& messages() { return (_messages); }
};