#pragma once

#include "jgl.h"

#include "Routine/erelia_console_routine.h"

#include "Widget/Commun/erelia_console_output.h"
#include "Widget/Commun/erelia_console_input.h"
#include "Widget/Commun/erelia_console_parser.h"

class Console_manager : public jgl::Widget
{
private:
	static Console_manager* _instance;

	Console_output* _console_output;
	Console_input* _console_input;
	Console_parser* _console_parser;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Console_manager(jgl::Widget* p_parent = nullptr);

	void _send_command();
	void _initialize_server();
	void _initialize_client();
	void _initiate();

public:
	static Console_manager* instanciate(jgl::Widget* p_parent = nullptr);
	static Console_manager* instance();

	Console_output* console_output() { return (_console_output); }
	Console_input* console_input() { return (_console_input); }
	Console_parser* console_parser() { return (_console_parser); }

	jgl::Bool console_active() { return (_console_input->is_selected()); }
	jgl::Bool console_entry_pointed() { return (_console_input->text_entry()->is_pointed()); }
};