#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"
#include "Network/erelia_client_manager.h"
#include "Network/erelia_server_manager.h"

class Abstract_manager
{
protected:
	virtual void _initialize_client() = 0;
	virtual void _initialize_server() = 0;

	void _initiate();

public:
	Abstract_manager();
};