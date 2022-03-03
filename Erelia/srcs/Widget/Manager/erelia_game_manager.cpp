#include "erelia.h"

Game_manager* Game_manager::_instance = nullptr;

void Game_manager::_on_geometry_change()
{
	_map_manager->set_geometry(0, _area);
	_entity_manager->set_geometry(0, _area);
	_player_manager->set_geometry(0, _area);
	_console_manager->set_geometry(0, _area);

	jgl::Vector2Int label_size = jgl::Vector2Int(_area.x, 50);
	jgl::Vector2Int pos = _area / 2 - label_size / 2;

	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_message_label[i]->set_geometry(pos + jgl::Vector2Int(0, label_size.y * i), label_size);
	}
}

void Game_manager::_render_singleplayer()
{

}

void Game_manager::_render_multiplayer()
{

}

void Game_manager::_render_host()
{

}

void Game_manager::_render()
{
	if (_mode == Connection_mode::Singleplayer)
	{
		_render_singleplayer();
	}
	else if (_mode == Connection_mode::Multiplayer)
	{
		_render_multiplayer();
	}
	else if (_mode == Connection_mode::Host)
	{
		_render_host();
	}
}

jgl::Bool Game_manager::_update_singleplayer()
{
	if (_map_manager->active() == false)
		_map_manager->activate();
	if (_entity_manager->active() == false)
		_entity_manager->activate();
	if (_player_manager->active() == false)
		_player_manager->activate();
	if (_console_manager->active() == false)
		_console_manager->activate();

	return (false);
}

jgl::Bool Game_manager::_update_multiplayer()
{
	return (false);
}

jgl::Bool Game_manager::_update_host_unknow()
{
	set_message_label_text("Connection : Confirmation", "...");
	return (false);
}

jgl::Bool Game_manager::_update_host_rejected()
{
	if (_last_connection_state != Connection::State::Refused)
		set_message_label_text("Connection : Refused", "Try to update your game");
	return (false);
}

jgl::Bool Game_manager::_update_host_accepted()
{
	if (_last_connection_state != Connection::State::Accepted)
	{
		set_message_label_text("Connection : Accepted", "Connect to account [" + _username + "]", "...");
		connect_client();
	}
	return (false);
}

jgl::Bool Game_manager::_update_host()
{
	if (_server->is_active() == false)
	{
		set_message_label_text("Server not active");
		return (false);
	}
	if (_client->is_connected() == false)
		set_message_label_text("Client not connected");
	else
	{
		if (_client->connection()->state() == Connection::State::Unknown)
			_update_host_unknow();
		if (_client->connection()->state() == Connection::State::Refused)
			_update_host_rejected();
		else if (_client->connection()->state() == Connection::State::Accepted)
			_update_host_accepted();

		_last_connection_state = _client->connection()->state();
	}
	return (false);
}

jgl::Bool Game_manager::_update()
{

	if (_client != nullptr)
		_client->update();
	if (_server != nullptr)
		_server->update();

	if (_mode == Connection_mode::Singleplayer)
	{
		return (_update_singleplayer());
	}
	else if (_mode == Connection_mode::Multiplayer)
	{
		return (_update_multiplayer());
	}
	else if (_mode == Connection_mode::Host)
	{
		return (_update_host());
	}
	else
	{
		return (false);
	}
}

void Game_manager::_initialize_client()
{

}

void Game_manager::_initialize_server()
{

}

Game_manager::Game_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_mode = p_mode;
	_engine = Engine::instanciate();
	_gamemode = Gamemode::Builder;

	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_message_label[i] = new jgl::Text_label("", this);
		_message_label[i]->box().set_color(jgl::Color(0, 0, 0, 0), jgl::Color(0, 0, 0, 0));
		_message_label[i]->label().set_text_color(jgl::Color::white());
		_message_label[i]->label().set_text_outline_color(jgl::Color::white());
		_message_label[i]->label().set_horizontal_align(jgl::Horizontal_alignment::Centred);
		_message_label[i]->label().set_vertical_align(jgl::Vertical_alignment::Centred);
	}

	if (p_mode == Connection_mode::Singleplayer)
	{

	}
	else if (p_mode == Connection_mode::Multiplayer)
	{
		_initialize_client();
	}
	else if (p_mode == Connection_mode::Host)
	{
		start_server();
		start_client("localhost");
		_initialize_server();
		_initialize_client();
	}

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

void Game_manager::instanciate_singleplayer(jgl::String p_world_name, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Singleplayer, p_parent);
	_instance->desactivate_message_label();
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->launch_map(p_world_name);
}

void Game_manager::instanciate_multiplayer(jgl::String p_server_address, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Multiplayer, p_parent);
	_instance->activate_message_label();
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->start_client(p_server_address);
	_instance->set_client_info(p_player_username, p_player_password);
}

void Game_manager::instanciate_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent)
{
	_instance = new Game_manager(Connection_mode::Host, p_parent);
	_instance->activate_message_label();
	_instance->set_geometry(0, jgl::Application::active_application()->size());
	_instance->launch_map(p_world_name);
	_instance->set_client_info(p_player_username, p_player_password);
}

void Game_manager::set_message_label_text(jgl::String p_text_a, jgl::String p_text_b, jgl::String p_text_c)
{
	_message_label[0]->label().set_text(p_text_a);
	_message_label[1]->label().set_text(p_text_b);
	_message_label[2]->label().set_text(p_text_c);
}

void Game_manager::activate_message_label()
{
	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_message_label[i]->activate();
	}
}

void Game_manager::desactivate_message_label()
{
	for (jgl::Size_t i = 0; i < 3; i++)
	{
		_message_label[i]->desactivate();
	}
}

void Game_manager::set_client_info(jgl::String p_username, jgl::String p_password)
{
	_username = p_username;
	_password = p_password;
}

void Game_manager::connect_client()
{
	if (_client == nullptr)
		return;

	Message msg(Server_message::Connection_request);

	msg << _username;
	msg << _password;

	_client->send(msg);
}

void Game_manager::start_client(jgl::String p_address)
{
	_client = new Client();
	_client->connect(p_address, SERVER_PORT);
}

void Game_manager::start_server()
{
	_server = new Server(SERVER_PORT);
	_server->set_key(14567);
	_server->start();
}

void Game_manager::launch_map(jgl::String p_map_name)
{
	_engine->load_map(Path_atlas::world_path + p_map_name);
}

Game_manager* Game_manager::instance()
{
	return (_instance);
}