#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_abstract_screen.h"

#include "Routine/erelia_loading_routine.h"

class Loading_screen : public Abstract_screen
{
protected:
	void _on_geometry_change();
	void _render();
	
	jgl::Bool _update();

	jgl::Text_label* _messages[3];

	void _set_text(jgl::String p_text_a, jgl::String p_text_b = "", jgl::String p_text_c = "");

	void _initialize_server();
	void _initialize_client();
	
	static Loading_screen* _instance;

	Loading_screen(jgl::Widget* p_parent);

public:
	void start();
	
	void load_monster();

	static Loading_screen* instanciate(jgl::Widget* p_parent);
	static Loading_screen* instance() { return (_instance); }
};