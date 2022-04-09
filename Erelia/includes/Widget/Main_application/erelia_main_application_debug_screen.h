#pragma once

#include "jgl.h"

class Debug_screen : public jgl::Widget, public jgl::Singleton_widget<Debug_screen>
{
	friend class jgl::Singleton_widget<Debug_screen>;
private:
	jgl::Widget_component::Text_label* _lines[3][30];

	void _render();
	void _on_geometry_change();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

	Debug_screen(jgl::Widget* p_parent);
public:

	void set_text(jgl::Size_t line, jgl::Size_t row, jgl::String p_text);
};