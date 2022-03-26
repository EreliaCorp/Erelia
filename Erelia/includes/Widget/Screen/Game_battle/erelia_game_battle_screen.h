#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Game_battle_screen : public Abstract_screen, public jgl::Singleton_widget<Game_battle_screen>
{
public:
	enum class Status
	{
		Pre_fight,
		Preparation,
		Round,
		Post_fight
	};
	enum class Event
	{
		Fight_ended
	};
	struct Context
	{

	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;
	typedef jgl::Singleton< jgl::State_machine<Status> > State_machine;
	
private:
	Context* _context;
	void _on_geometry_change();

public:
	Game_battle_screen(jgl::Widget* p_parent);
	void focus();
	void unfocus();
};

#define GAME_BATTLE_SCREEN_ACTIVITY_PARAM [&](Game_battle_screen::Context& p_context)