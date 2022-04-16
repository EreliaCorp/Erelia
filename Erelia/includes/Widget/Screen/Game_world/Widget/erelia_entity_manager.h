#pragma once

#include "jgl.h"

#include "Widget/Abstract_widget/erelia_abstract_manager.h"

class Entity_manager : public Abstract_manager, public jgl::Updater_widget
{
private:
	jgl::Timer _entity_updater_timer;

	jgl::Array<jgl::Long> _entity_to_ask;
	jgl::Map<jgl::Long, jgl::Bool> _entity_received;

	void _on_geometry_change();

	jgl::Bool _update();

	void _send_entity_data();
	void _request_entity_info();

	void _receive_entity_data(Message& p_msg);
	void _receive_entity_suppression_command(Message& p_msg);
	void _receive_entity_info(Message& p_msg);
	void _receive_request_entity_info(Connection* p_client, Message& p_msg);

	void _initialize_server();
	void _initialize_client();

public:
	Entity_manager(jgl::Widget* p_parent = nullptr);
	//void receive_entity_data(Message& p_msg);

	static jgl::Size_t nb_update;
	static jgl::Size_t nb_pos_update;
};