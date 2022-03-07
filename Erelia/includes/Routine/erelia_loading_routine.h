#pragma once

#include "jgl.h"
#include "Network/erelia_network_definition.h"

namespace Routine
{
	void treat_ID_request(Connection* p_client, Message& p_msg);
	void receive_player_ID_data(Message& p_msg);
}