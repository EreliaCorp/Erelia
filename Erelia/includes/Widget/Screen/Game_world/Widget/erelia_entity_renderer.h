#pragma once

#include "jgl.h"

#include "Widget/Abstract_widget/erelia_overworld_widget.h"

class Entity_renderer : public Overworld_widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	Entity_renderer(jgl::Widget* p_parent = nullptr);
};