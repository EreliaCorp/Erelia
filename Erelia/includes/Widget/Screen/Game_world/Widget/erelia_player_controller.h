#pragma once

#include "jgl.h"

class Player_controller : public jgl::Updater_widget
{
private:
	void _on_geometry_change();

	jgl::Bool _update();

public:
	Player_controller(jgl::Widget* p_parent);
};