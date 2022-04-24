#include "Widget/Screen/Game_world/erelia_game_world_screen.h"
#include "structure/Atlas/erelia_account_atlas.h"
#include "Widget/commun/erelia_console_manager.h"

void Game_world_screen::_on_geometry_change()
{
	_map_manager->set_geometry(0, _area);
	_player_manager->set_geometry(0, _area);
	_player_interacter->set_geometry(0, _area);
	_entity_manager->set_geometry(0, _area);
	_wrap_renderer->set_geometry(0, _area);
}

void Game_world_screen::_initialize_server()
{
}

void Game_world_screen::_initialize_client()
{
	Client_manager::client()->add_activity(Server_message::Gamemode_message, CLIENT_ACTIVITY{
			_receive_gamemode_change(p_msg);
		});
}

Game_world_screen::Game_world_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	State_machine::instanciate();
	Publisher::instanciate();

	_map_manager = new Map_manager(this);
	_map_manager->activate();

	_player_manager = new Player_manager(this);
	_player_manager->activate();

	_player_interacter = new Player_interacter(this);
	_player_interacter->activate();

	_entity_manager = new Entity_manager(this);
	_entity_manager->activate();
	
	_wrap_renderer = new Wrap_renderer(this);
	_wrap_renderer->activate();


	Publisher::instance()->subscribe(Game_world_screen::Event::Go_adventure, GAME_WORLD_SCREEN_ACTIVITY_PARAM{
			_player_interacter->publisher()->notify(Player_interacter::Event::Go_adventure);
		});
	Publisher::instance()->subscribe(Game_world_screen::Event::Go_builder, GAME_WORLD_SCREEN_ACTIVITY_PARAM{
			_player_interacter->publisher()->notify(Player_interacter::Event::Go_builder);
		});
	Publisher::instance()->subscribe(Game_world_screen::Event::Go_NPC_creator, GAME_WORLD_SCREEN_ACTIVITY_PARAM{
			_player_interacter->publisher()->notify(Player_interacter::Event::Go_NPC_creator);
		});

	_initiate();
}

void Game_world_screen::_receive_gamemode_change(Message& p_msg)
{
	Event new_event;

	p_msg >> new_event;

	THROW_INFORMATION("Receiving gamemode [" + jgl::itoa(static_cast<jgl::Int>(new_event)) + "]");
	Publisher::instance()->notify(new_event);
}

void Game_world_screen::focus()
{
	THROW_INFORMATION("Focus on game world screen");
	Publisher::instance()->notify(Game_world_screen::Event::Go_NPC_creator);
	Console_manager::instance()->activate();
	if (Server_manager::instance() != nullptr)
		Server_manager::server()->set_logout_function([&](Connection* p_client, jgl::Data_contener& p_param) {
			Account* tmp_account = Account_atlas::instance()->active_account(p_client->id());

			if (tmp_account != nullptr)
			{
				jgl::Long entity_id = tmp_account->id;
				Account_atlas::instance()->desactivate_account(p_client->id());

				static Message msg(Server_message::Entity_suppression);

				msg.clear();

				msg << entity_id;

				Server_manager::server()->send_to_all(msg, p_client);
			}
		});
}

void Game_world_screen::unfocus()
{
	THROW_INFORMATION("Unfocus on game world screen");
	Console_manager::instance()->desactivate();
}