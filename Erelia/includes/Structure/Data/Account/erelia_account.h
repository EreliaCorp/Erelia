#pragma once

#include "jgl.h"

#include "Network/erelia_network_definition.h"
#include "structure/Data/Monster/erelia_monster.h"

struct Account
{
	jgl::String username;
	jgl::String password;
	Connection* connection;
	jgl::Long id;
	jgl::Vector2 pos;
	Monster* monsters[6];
	jgl::Array<Monster*> monsters_stocked;

	Account(jgl::String p_username = "", jgl::String p_password = "");
};