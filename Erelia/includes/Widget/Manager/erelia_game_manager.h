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
public :
	enum class Loading_status
	{
		Error = -1,
		Connection_complete = 0,
		Timeout_multiplayer_connection = 1,
		Connection_refused = 2
	};
private:
	Engine* _engine;

	Map_manager* _map_manager;
	Entity_manager* _entity_manager;
	Player_manager* _player_manager;
	Console_manager* _console_manager;

	void _on_geometry_change();
	void _render();
	Game_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

	static Game_manager* _instance;
	Loading_status _loading_status = Loading_status::Error;

public:
	static void instanciate_singleplayer(jgl::String p_world_name, jgl::Widget* p_parent);
	static void instanciate_multiplayer(jgl::String p_server_address, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent);
	static void instanciate_host(jgl::String p_world_name, jgl::String p_player_username, jgl::String p_player_password, jgl::Widget* p_parent);

	~Game_manager();
	static Game_manager* instance();

	void set_loading_status(Loading_status p_status);
	Loading_status loading_status();
	
	void connect_host(jgl::String p_username, jgl::String p_password);
	void connect_client(jgl::String p_username, jgl::String p_password);
	void start_client(jgl::String p_address);
	void start_server();
	void launch_map(jgl::String p_map_name);
};
