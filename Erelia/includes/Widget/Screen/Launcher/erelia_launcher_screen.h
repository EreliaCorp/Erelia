#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

#include "widget/erelia_launcher_connection_manager.h"
#include "widget/erelia_launcher_registration_manager.h"
#include "widget/erelia_launcher_menu.h"
#include "widget/erelia_launcher_message_output.h"

class Launcher_screen : public Abstract_screen, public jgl::Singleton_widget<Launcher_screen>
{
	friend class  jgl::Singleton_widget<Launcher_screen>;
public:
	enum class Event
	{
		Connection_complete
	};
	struct Context
	{

	};

	typedef jgl::Singleton< jgl::Publisher<Event, Context> > Publisher;

private:
	Connection_manager* _connection_manager;
	Registration_manager* _registration_manager;
	Launcher::Menu* _menu;
	Launcher::Message_output* _message_output;

	void _on_geometry_change();

	Launcher_screen(jgl::Widget* p_parent);

public:
	void set_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");

	const jgl::String& username() { return (_menu->username()); }
	const jgl::String& password() { return (_menu->password()); }
	
	void focus();
	void unfocus();
};

#define LAUNCHER_SCREEN_ACTIVITY_PARAM [&](Launcher_screen::Context& p_context)