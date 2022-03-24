#pragma once

#include "jgl.h"

#include "widget/Abstract_widget/erelia_abstract_manager_widget.h"

class Connection_manager : public Abstract_manager_widget
{
private:
	void _on_geometry_change(jgl::Vector2Int p_anchor, jgl::Vector2Int p_area);

	void _initialize_client();
	void _initialize_server();

	jgl::Bool _update();

public:
	Connection_manager(jgl::Widget* p_parent);
};