#pragma once

#include "jgl.h"

class Translation_atlas
{
private:
	static jgl::Map<jgl::String, jgl::String> _strings;

public:
	static void load(jgl::String p_path);
	static jgl::String string(jgl::String p_key);
};