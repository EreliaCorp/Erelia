#pragma once

#include "jgl.h"

#include "widget/Abstract_widget/erelia_abstract_manager_widget.h"

class Registration_manager : public Abstract_manager_widget
{
private:
	jgl::Button* _button;

	void _on_geometry_change();

	void _initialize_client();
	void _initialize_server();

	jgl::Bool _update();

public:
	Registration_manager(jgl::Widget* p_parent);
};