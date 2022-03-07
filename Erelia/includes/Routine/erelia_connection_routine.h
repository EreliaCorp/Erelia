#pragma once

#include "jgl.h"
#include "Network/erelia_network_definition.h"

namespace Routine
{
	void treat_connection_request(Connection* p_client, Message& p_msg);
	void treat_registration_request(Connection* p_client, Message& p_msg);
	void treat_connection_message(Message& p_msg);
	void send_connection_request(jgl::String p_username, jgl::String p_password);
	void send_registration_request(jgl::String p_username, jgl::String p_password);
};