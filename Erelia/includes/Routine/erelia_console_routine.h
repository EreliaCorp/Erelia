#pragma once

#include "jgl.h"
#include "Network/erelia_network_definition.h"

namespace Routine
{
	void treat_command_input(Connection* p_client, Message& p_msg);
	void receive_console_message(Message& p_msg);
}