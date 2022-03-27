#pragma once

#include "jgl.h"
#include "widget/Abstract_widget/erelia_overworld_widget.h"
#include "network/erelia_network_definition.h"
#include "structure/Data/Map/erelia_map.h"

class Map_renderer : public Overworld_widget
{
private:
	void _on_geometry_change();
	void _render();

public:
	Map_renderer(jgl::Widget* p_parent);
};