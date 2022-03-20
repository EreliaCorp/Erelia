#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"
#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

class Manager_widget : public jgl::Widget
{
protected:
	void _render() final;

	virtual void _initialize_client();
	virtual void _initialize_server();

	void _initiate();

public:
	Manager_widget(jgl::Widget* p_parent);
};