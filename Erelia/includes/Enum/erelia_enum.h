#pragma once

#include "jgl.h"

enum class Connection_mode
{
	Singleplayer = 0,
	Multiplayer = 1,
	Host = 2
};

enum class Server_message
{
	Error = -1,
	Connection_request = 0,
	Connection_rejected = 1,
	Connection_confirmation = 2
};

#define SERVER_PORT 25600
using Message = jgl::Message<Server_message>;
using Client = jgl::Client<Server_message>;
using Server = jgl::Server<Server_message>;
using Connection = jgl::Connection<Server_message>;