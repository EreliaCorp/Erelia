#pragma once

#include "jgl.h"

#include "network/erelia_network_definition.h"
#include "widget/Abstract_widget/erelia_abstract_manager_widget.h"

class Registration_manager : public Abstract_manager_widget
{
private:
	jgl::Button* _button;

	void _on_geometry_change();

	void _initialize_client();
	void _initialize_server();

	jgl::Bool _update();

	void _send_registration_request();
	void _treat_registration_request(Message& p_msg);
	void _treat_registration_approuval(Message& p_msg);
	void _treat_registration_rejection(Message& p_msg);

public:
	Registration_manager(jgl::Widget* p_parent);
};