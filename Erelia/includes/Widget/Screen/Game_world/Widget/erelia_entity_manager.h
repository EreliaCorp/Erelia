#pragma once

#include "jgl.h"

#include "Widget/Abstract_widget/erelia_abstract_manager.h"

class Entity_manager : public Abstract_manager, public jgl::Updater_widget
{
private:
	jgl::Timer _entity_updater_timer;

	void _on_geometry_change();

	jgl::Bool _update();

	void _receive_entity_data(Message& p_msg);
	void _receive_entity_suppression_command(Message& p_msg);

	void _initialize_server();
	void _initialize_client();

public:
	Entity_manager(jgl::Widget* p_parent = nullptr);
	//void receive_entity_data(Message& p_msg);
};