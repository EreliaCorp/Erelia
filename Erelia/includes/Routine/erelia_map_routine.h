#pragma once

#include "network/erelia_network_definition.h"

namespace Routine
{
	void treat_chunk_request_routine(Connection* p_client, Message& p_msg);
	void received_chunk_data_routine(Message& p_msg);

	void treat_chunk_modification(Connection* p_client, Message& p_msg);
	void received_chunk_modification(Message& p_msg);
}