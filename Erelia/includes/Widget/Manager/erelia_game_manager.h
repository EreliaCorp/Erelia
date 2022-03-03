#pragma once

#include "jgl.h"
#include "Enum/erelia_enum.h"

#include "Structure/Data/Engine/erelia_engine.h"

#include "Widget/Manager/erelia_map_manager.h"
#include "Widget/Manager/erelia_entity_manager.h"
#include "Widget/Manager/erelia_player_manager.h"
#include "Widget/Manager/erelia_console_manager.h"


class Game_manager : public jgl::Widget
{
private:
	Connection_mode _mode;
	Connection::State _last_connection_state;

	Engine* _engine;

	Client* _client;
	Server* _server;
	jgl::Map<jgl::String, jgl::String> _account_map;

	Gamemode _gamemode;

	jgl::String _username = "";
	jgl::String _password = "";

	jgl::Text_label* _message_label[3];

	Map_manager* _map_manager;
	Entity_manager* _entity_manager;
	Player_manager* _player_manager;
	Console_manager* _console_manager;

	void _on_geometry_change();

	void _render_singleplayer();
	void _render_multiplayer();
	void _render_host();
	void _render();

	jgl::Bool _update_singleplayer();
	jgl::Bool _update_multiplayer();

	jgl::Bool _update_host_unknow();
	jgl::Bool _update_host_rejected();
	jgl::Bool _update_host_accepted();
	jgl::Bool _update_host();

	jgl::Bool _update();

	Game_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

	static Game_manager* _instance;

	void _initialize_client();
	void _initialize_server();

public:
	static void instanciate_singleplayer(jgl::String p_world_name, jgl::Widget* p_parent);
	static void instanciate_multiplayer(jgl::String p_server_address, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent);
	static void instanciate_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent);

	~Game_manager();
	static Game_manager* instance();

	void set_connection_mode(Connection_mode p_mode) { _mode = p_mode; }
	Connection_mode connection_mode() { return (_mode); }

	void set_gamemode(Gamemode p_gamemode) { _gamemode = p_gamemode; }
	Gamemode gamemode() { return (_gamemode); }

	Client* client() { return(_client); }
	Server* server() { return(_server); }

	void set_message_label_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");
	void activate_message_label();
	void desactivate_message_label();

	void received_player_info(Message& p_msg);

	void set_client_info(jgl::String p_username, jgl::String p_password);

	void start_client(jgl::String p_address);
	void connect_client();

	void start_server();

	void launch_map(jgl::String p_map_name);
};
