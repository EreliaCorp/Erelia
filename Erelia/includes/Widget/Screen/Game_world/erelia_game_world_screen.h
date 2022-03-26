#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Game_world_screen : public Abstract_screen
{
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

public:
	Game_world_screen(jgl::Widget* p_parent);
	void focus();
	void unfocus();
};

#define GAME_WORLD_SCREEN_ACTIVITY_PARAM [&](Game_world_screen::Context& p_context)