#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"

struct Account
{
	jgl::String username;
	jgl::String password;
	Connection* connection;
	jgl::Long id;
	jgl::Vector2 pos;

	Account(jgl::String p_username = "", jgl::String p_password = "");
};