#include "erelia.h"

Account::Account(jgl::String p_username, jgl::String p_password)
{
	username = p_username;
	password = p_password;
	connection = nullptr;
	id = -1;
	for (jgl::Size_t i = 0; i < 6; i++)
		monsters[i] = nullptr;
}