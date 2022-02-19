#include "erelia.h"

UI_configuration_file Singleton_atlas::configuration_file;

Client* Singleton_atlas::_client = nullptr;
Server* Singleton_atlas::_server = nullptr;

Client* Singleton_atlas::instanciate_client()
{
	if (_client == nullptr)
	{
		std::cout << "Initialize client" << std::endl;
		_client = new Client();
	}
	return (_client);
}

Server* Singleton_atlas::instanciate_server()
{
	if (_server == nullptr)
	{
		std::cout << "Initialize server" << std::endl;
		_server = new Server(SERVER_PORT);
	}
	return (_server);
}

Client* Singleton_atlas::client()
{
	return (_client);
}

Server* Singleton_atlas::server()
{
	return (_server);
}