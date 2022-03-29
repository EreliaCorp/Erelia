#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"
#include "Widget/Screen/Game_world/Widget/erelia_map_renderer.h"
#include "Widget/Screen/Game_world/Widget/erelia_map_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_player_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_player_interacter.h"
#include "Widget/Screen/Game_world/Widget/erelia_entity_manager.h"
#include "Widget/Screen/Game_world/Widget/erelia_entity_renderer.h"

class Game_world_screen : public Abstract_screen, public Abstract_manager, public jgl::Singleton_widget<Game_world_screen>
{
	friend class  jgl::Singleton_widget<Game_world_screen>;
public:
	enum class Mode
	{
		Adventure,
		Builder,
		Area_builder
	};
	enum class Event
	{
		Go_adventure,
		Go_builder,
		Go_area_builder
	};
	struct Context
	{
		jgl::Bool area_mode = false;
	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Mode> > State_machine;

private:
	void _on_geometry_change();

	void _initialize_server();
	void _initialize_client();

	Game_world_screen(jgl::Widget* p_parent);

	Map_renderer* _map_renderer;
	Map_manager* _map_manager;
	Player_manager* _player_manager;
	Player_interacter* _player_interacter;
	Entity_manager* _entity_manager;
	Entity_renderer* _entity_renderer;

	void _receive_gamemode_change(Message& p_msg);

public:
	void focus();
	void unfocus();
};

#define GAME_WORLD_SCREEN_ACTIVITY_PARAM [&](Game_world_screen::Context& p_context)