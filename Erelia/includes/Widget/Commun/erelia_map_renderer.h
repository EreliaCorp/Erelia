#pragma once

#include "erelia_graphical_widget.h"

class Map_renderer : public Graphical_widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	Map_renderer(jgl::Widget *p_parent);
};