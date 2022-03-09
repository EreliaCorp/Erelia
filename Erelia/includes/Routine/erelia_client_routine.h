#pragma once

#include "jgl.h"
#include "Network/erelia_network_definition.h"

namespace Routine
{
	void treat_ping_request(Connection* p_client, Message& p_msg);
	void receive_ping_result(Message& p_msg);

	void client_logout_routine(Connection* p_client);
	void receive_gamemode_change(Message& p_msg);
	void receive_brush_size_change(Message& p_msg);
	void receive_brush_type_change(Message& p_msg);
	void receive_brush_type_data_change(Message& p_msg);
}