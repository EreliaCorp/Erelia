#pragma once

#include "jgl.h"

#include "Enum/erelia_enum.h"

#include "Structure/File/erelia_UI_configuration_file.h"

class Singleton_atlas
{
private:
	static Client* _client;
	static Server* _server;

	Singleton_atlas() = delete;

public:
	static UI_configuration_file configuration_file;
	static Client* instanciate_client();
	static Server* instanciate_server();
	static Client* client();
	static Server* server();
};