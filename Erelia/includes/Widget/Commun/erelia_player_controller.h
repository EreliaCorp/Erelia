#pragma once

#include "Widget/Commun/erelia_graphical_widget.h"

class Player_controller : public Graphical_widget
{
private:
	void _on_geometry_change();
	void _render();

	jgl::Bool _update();
	void _send_motion_command(jgl::Vector2Int p_delta);

public:
	Player_controller(jgl::Widget* p_parent = nullptr);
};