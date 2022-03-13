#pragma once

#include "jgl.h"

#include "Routine/erelia_entity_routine.h"

#include "Widget/Commun/erelia_graphical_widget.h"

class Entity_manager : public Graphical_widget
{
private:
	jgl::Timer _entity_updater_timer;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();
	jgl::Bool _fixed_update();

	void _initialize_server();
	void _initialize_client();
	void _initiate();

	Entity_manager(jgl::Widget* p_parent = nullptr);

	static Entity_manager* _instance;
public:
	void receive_entity_data(Message& p_msg);

	static Entity_manager* instanciate(jgl::Widget* p_parent = nullptr);
	static Entity_manager* instance();
};