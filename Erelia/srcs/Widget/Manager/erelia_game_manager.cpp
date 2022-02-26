#include "erelia.h"

Game_manager* Game_manager::_instance = nullptr;

void Game_manager::_on_geometry_change()
{
	_map_manager->set_geometry(0, _area);
	_entity_manager->set_geometry(0, _area);
	_player_manager->set_geometry(0, _area);
	_console_manager->set_geometry(0, _area);
}

void Game_manager::_render()
{

}

Game_manager::Game_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_loading_status = Loading_status::Error;
	_engine = Engine::instanciate();

	_map_manager = Map_manager::instanciate(p_mode, this);
	_entity_manager = Entity_manager::instanciate(p_mode, this);
	_player_manager = Player_manager::instanciate(p_mode, this);
	_console_manager = Console_manager::instanciate(p_mode, this);
}

Game_manager::~Game_manager()
{
	if (_map_manager != nullptr)
		delete _map_manager;
	if (_entity_manager != nullptr)
		delete _entity_manager;
	if (_player_manager != nullptr)
		delete _player_manager;
	if (_console_manager != nullptr)
		delete _console_manager;
	if (_engine != nullptr)
		delete _engine;
}

void Game_manager::set_loading_status(Game_manager::Loading_status p_status)
{
	_loading_status = p_status;
}

Game_manager::Loading_status Game_manager::loading_status()
{
	return (_loading_status);
}


void Game_manager::instanciate_singleplayer(jgl::String p_world_name, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Singleplayer, p_parent);
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->launch_map(p_world_name);
	_instance->set_loading_status(Game_manager::Loading_status::Connection_complete);
}

void Game_manager::instanciate_multiplayer(jgl::String p_server_address, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Multiplayer, p_parent);
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->start_client(p_server_address);

	jgl::Ulong starting_time = jgl::Application::active_application()->getTime();

	while (Singleton_atlas::client()->is_connected() == false && jgl::Application::active_application()->getTime() < starting_time + 2000) {}
	while (Singleton_atlas::client()->connection()->state() == Connection::State::Unknown && jgl::Application::active_application()->getTime() < starting_time + 2000)
	{
		Singleton_atlas::client()->update();
	}

	if (jgl::Application::active_application()->getTime() >= starting_time + 2000)
	{
		_instance->set_loading_status(Game_manager::Loading_status::Timeout_multiplayer_connection);
		Singleton_atlas::client()->disconnect();
	}
	else if (Singleton_atlas::client()->connection()->state() == Connection::State::Refused)
	{
		_instance->set_loading_status(Game_manager::Loading_status::Connection_refused);
		Singleton_atlas::client()->disconnect();
	}
	else
	{
		_instance->connect_client(p_player_username, p_player_password);
		_instance->set_loading_status(Game_manager::Loading_status::Connection_complete);
	}
}

void Game_manager::instanciate_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Host, p_parent);
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->launch_map(p_world_name);
	_instance->start_server();
	_instance->connect_host(p_player_username, p_player_password);
	_instance->set_loading_status(Game_manager::Loading_status::Connection_complete);
}

void Game_manager::connect_client(jgl::String p_username, jgl::String p_password)
{
	Message msg(Server_message::Connection_request);

	msg << p_username;
	msg << p_password;

	Singleton_atlas::client()->send(msg);
}

void Game_manager::connect_host(jgl::String p_username, jgl::String p_password)
{
	
}

void Game_manager::start_client(jgl::String p_address)
{
	Singleton_atlas::instanciate_client();
	Singleton_atlas::client()->connect(p_address, SERVER_PORT);
}

void Game_manager::start_server()
{
	Singleton_atlas::instanciate_server();
	Singleton_atlas::server()->set_key(14567);
	Singleton_atlas::server()->start();
}

void Game_manager::launch_map(jgl::String p_map_name)
{
	_engine->load_map(Path_atlas::world_path + p_map_name);
}

Game_manager* Game_manager::instance()
{
	return (_instance);
}