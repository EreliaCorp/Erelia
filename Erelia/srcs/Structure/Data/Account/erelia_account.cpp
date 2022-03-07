#include "erelia.h"

Account::Account(jgl::String p_username, jgl::String p_password)
{
	username = p_username;
	password = p_password;
	connection = nullptr;
	id = -1;
}