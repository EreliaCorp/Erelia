#pragma once

#include "jgl.h"

#include "Enum/erelia_enum.h"

#include "Structure/File/erelia_UI_configuration_file.h"

class Singleton_atlas
{
private:
	Singleton_atlas() = delete;

public:
	static UI_configuration_file configuration_file;
};