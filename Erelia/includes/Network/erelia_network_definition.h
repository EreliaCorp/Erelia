#pragma once

#include "jgl.h"

enum Server_message
{
	Ping = -2,
	Error = -1,
	Register_request = 0,
	Connection_request = 1,
	Connection_accepted = 2,
	Connection_screen_communication = 3,
	ID_request = 4,
	ID_data = 5,
	Chunk_request = 6,
	Chunk_data = 7,
	Entity_data = 8,
	Player_movement = 9,
	Entity_suppression = 10,
	Command_input = 11,
	Console_message = 12,
	Chunk_modification = 13,
	Gamemode_message = 14,
	Brush_size_message = 15,
	Brush_type_message = 16,
	Brush_type_data_message = 17
};

#define SERVER_PORT 26500
using Connection = jgl::Connection<Server_message>;
using Message = jgl::Message<Server_message>;
using Client = jgl::Client<Server_message>;
using Server = jgl::Server<Server_message>;

#define SERVER_ACTIVITY [&](Connection* p_client, Message& p_msg, jgl::Data_contener& p_param)
#define CLIENT_ACTIVITY [&](Message& p_msg, jgl::Data_contener& p_param)