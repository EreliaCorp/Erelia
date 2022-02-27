#pragma once

#include "jgl.h"

class Console_input : public jgl::Widget
{
private:
	jgl::Text_entry* _text_entry;

	void _render();
	void _on_geometry_change();

public:
	Console_input(jgl::Widget* p_parent);
	jgl::String text() { return (_text_entry->text());}
	void reset_text() { _text_entry->reset_text();}
	jgl::Bool is_selected() { return (_text_entry->is_selected()); }
	jgl::Text_entry* text_entry() { return (_text_entry); }
};