#pragma once

#include "jgl.h"

class Player_file
{
private:

public:
	static struct Account* load(jgl::String p_path);
	static void save(jgl::String p_path, struct Account* p_account);
};