#pragma once

#include "jgl.h"

#include "Enum/erelia_enum.h"

#include "Widget/Commun/erelia_console_output.h"
#include "Widget/Commun/erelia_console_input.h"

#include "Widget/Singleplayer/erelia_singleplayer_console_parser.h"

class Console_manager : public jgl::Widget
{
private:
	static Console_manager* _instance;

	Console_output* _console_output;
	Console_input* _console_input;
	Abstract_console_parser* _console_parser;

	void _on_geometry_change();
	void _render();
	void _change_connection_mode(Connection_mode p_mode);
	void _load_ui_file();

	jgl::Bool _update();

	Console_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

public:
	static Console_manager* instanciate(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);
	static Console_manager* instance();
	jgl::Bool console_active() { return (_console_input->is_selected()); }
};