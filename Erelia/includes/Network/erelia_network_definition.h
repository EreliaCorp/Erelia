#pragma once

#include "jgl.h"

enum Server_message
{
	Ping,
	Registration_request,
	Registration_accepted,
	Registration_refused,
	Connection_request,
	Connection_accepted,
	Connection_refused,
	Chunk_request,
	Chunk_data,
	Chunk_modification,
	Player_movement,
	Entity_data,
	Entity_suppression,
	Command_input,
	Console_message,
	Gamemode_message,
	Brush_size_message,
	Brush_type_message,
	Brush_type_data_message,
	Monster_area_value,
	Encounter_modification,
	Place_teleport_data_request,
	Place_teleport_data,
	Place_teleporter
};

#define SERVER_PORT 26500

using Connection = jgl::Connection<Server_message>;
using Message = jgl::Message<Server_message>;
using Client = jgl::Client<Server_message>;
using Server = jgl::Server<Server_message>;

#define SERVER_ACTIVITY [&](Connection* p_client, Message& p_msg, jgl::Data_contener& p_param)
#define CLIENT_ACTIVITY [&](Message& p_msg, jgl::Data_contener& p_param)