#pragma once

#include "jgl.h"

class Console_input : public jgl::Widget
{
private:
	jgl::Size_t _old_line_index = 0;
	jgl::Array<jgl::String > _old_line;
	jgl::Text_entry* _text_entry;

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();

public:
	Console_input(jgl::Widget* p_parent);
	jgl::String text() { return (_text_entry->text());}
	void reset_text() { _old_line.push_back(_text_entry->text()); _text_entry->reset_text(); _old_line_index = _old_line.size(); }
	jgl::Bool is_selected() { return (_text_entry->is_selected()); }
	jgl::Text_entry* text_entry() { return (_text_entry); }
};