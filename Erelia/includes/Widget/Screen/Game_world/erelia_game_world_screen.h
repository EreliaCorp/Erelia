#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"
#include "Widget/Screen/Game_world/Widget/erelia_map_renderer.h"
#include "Widget/Screen/Game_world/Widget/erelia_map_manager.h"

class Game_world_screen : public Abstract_screen, public jgl::Singleton_widget<Game_world_screen>
{
	friend class  jgl::Singleton_widget<Game_world_screen>;
public:
	enum class Status
	{
		Adventure_mode,
		Builder_mode,
		Area_builder_mode
	};
	enum class Event
	{
		Go_adventure,
		Go_builder,
		Go_area_builder
	};
	struct Context
	{

	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Status> > State_machine;

private:
	void _on_geometry_change();

	Game_world_screen(jgl::Widget* p_parent);

	Map_renderer* _map_renderer;
	Map_manager* _map_manager;

public:
	void focus();
	void unfocus();
};

#define GAME_WORLD_SCREEN_ACTIVITY_PARAM [&](Game_world_screen::Context& p_context)