#pragma once

#include "jgl.h"

#include "network/erelia_network_definition.h"
#include "widget/Abstract_widget/erelia_abstract_manager.h"

class Connection_manager : public Abstract_manager, public jgl::Updater_widget
{
private:
	jgl::Button* _button;

	void _on_geometry_change();

	void _initialize_client();
	void _initialize_server();

	jgl::Bool _update();

	void _send_connection_request();
	void _treat_connection_request(Connection* p_client, Message& p_msg);
	void _treat_connection_approuval(Message& p_msg);
	void _treat_connection_rejection(Message& p_msg);

public:
	Connection_manager(jgl::Widget* p_parent);
};