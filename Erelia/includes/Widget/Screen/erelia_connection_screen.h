#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_abstract_screen.h"

#include "Routine/erelia_connection_routine.h"

class Connection_screen : public Abstract_screen
{
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

	jgl::Bool _initiate_state = false;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Connection_screen(jgl::Widget* p_parent);

	void _initialize_server();
	void _initialize_client();

	static Connection_screen* _instance;

public:
	void start();
	void set_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");

	static Connection_screen* instanciate(jgl::Widget* p_parent);
	static Connection_screen* instance() { return (_instance); }
};