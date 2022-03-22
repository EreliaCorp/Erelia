#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Launcher_screen : public Abstract_screen
{
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
	struct Data_input
	{
		jgl::Text_label* label;
		jgl::Text_entry* entry;

		Data_input();
		Data_input(jgl::String p_name, jgl::String p_value, jgl::Widget* p_parent);

		void set_geometry(jgl::Vector2Int p_anchor, jgl::Vector2Int p_area);
	};

	jgl::Frame* _layout;
	jgl::Frame* _logo;
	Data_input _username_input;
	Data_input _password_input;
	jgl::Button* _connect_button;
	jgl::Button* _register_button;

	jgl::Text_label* _messages_output[3];

	jgl::Bool _update();
	void _on_geometry_change();

public:
	void set_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");
	Launcher_screen(jgl::Widget* p_parent);
	void focus();
	void unfocus();
};

#define LAUNCHER_SCREEN_ACTIVITY_PARAM [&](Launcher_screen::Context& p_context)