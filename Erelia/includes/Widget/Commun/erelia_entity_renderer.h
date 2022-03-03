#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_graphical_widget.h"

class Entity_renderer : public Graphical_widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	Entity_renderer(jgl::Widget* p_parent);
};