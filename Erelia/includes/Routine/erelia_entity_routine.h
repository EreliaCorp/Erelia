#pragma once

#include "network/erelia_network_definition.h"

namespace Routine
{
	void treat_player_motion(Connection* p_client, Message& p_msg);
	void receive_entity_data(Message& p_msg);
	void receive_entity_suppression_command(Message& p_msg);
}