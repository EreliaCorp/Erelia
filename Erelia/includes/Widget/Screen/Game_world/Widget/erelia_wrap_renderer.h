#pragma once

#include "jgl.h"

#include "widget/Abstract_widget/erelia_overworld_widget.h"

class Wrap_renderer : public Overworld_widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	Wrap_renderer(jgl::Widget* p_parent);
};