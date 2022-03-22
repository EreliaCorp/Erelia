#pragma once

#include "jgl.h"

class Abstract_screen : public jgl::Widget
{
private:
	virtual void _on_geometry_change() = 0;
	void _render() final;

public:
	Abstract_screen(jgl::Widget* p_parent);
	virtual void focus() = 0;
	virtual void unfocus() = 0;
};