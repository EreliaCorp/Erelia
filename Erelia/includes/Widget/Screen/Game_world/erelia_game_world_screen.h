#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"
#include "Widget/Screen/Game_world/Widget/erelia_map_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_player_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_player_interacter.h"
#include "Widget/Screen/Game_world/Widget/erelia_entity_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_wrap_renderer.h"

class Game_world_screen : public Abstract_screen, public Abstract_manager, public jgl::Singleton_widget<Game_world_screen>
{
	friend class  jgl::Singleton_widget<Game_world_screen>;
public:
	enum class Mode
	{
		Adventure,
		Builder,
		NPC_creator
	};
	enum class Event
	{
		Go_adventure,
		Go_builder,
		Go_NPC_creator
	};
	struct Context
	{
		Entity* selected_id;
	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Mode> > State_machine;

private:
	void _on_geometry_change();

	void _initialize_server();
	void _initialize_client();

	Game_world_screen(jgl::Widget* p_parent);

	Map_manager* _map_manager;
	Player_manager* _player_manager;
	Player_interacter* _player_interacter;
	Entity_manager* _entity_manager;
	Wrap_renderer* _wrap_renderer;

	void _receive_gamemode_change(Message& p_msg);
public:
	void focus();
	void unfocus();
};

#define GAME_WORLD_SCREEN_ACTIVITY_PARAM [&](Game_world_screen::Context& p_context)