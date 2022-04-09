#pragma once

#include "widget/Abstract_widget/erelia_abstract_manager.h"
#include "widget/Commun/erelia_console_output.h"
#include "widget/Commun/erelia_console_input.h"
#include "widget/Commun/erelia_console_parser.h"

class Console_manager : public Abstract_manager, public jgl::Widget, public jgl::Singleton_widget<Console_manager>
{
	friend class jgl::Singleton_widget<Console_manager>;

private:
	Console_output* _console_output;
	Console_input* _console_input;
	Console_parser* _console_parser;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	void _send_command();
	void _initialize_server();
	void _initialize_client();

	void _treat_command_input(Connection* p_client, Message& p_msg);
	void _receive_console_message(Message& p_msg);
	void _treat_ping_request(Connection* p_client, Message& p_msg);
	void _receive_ping_result(Message& p_msg);

	Console_manager(jgl::Widget* p_parent);
public:
	Console_output* console_output() { return (_console_output); }
	Console_input* console_input() { return (_console_input); }
	Console_parser* console_parser() { return (_console_parser); }

	void send_global_message(jgl::String p_text);
	void send_private_message(jgl::String p_text, Connection* p_client);

	jgl::Bool console_active() { return (_console_input->is_selected()); }
	jgl::Bool console_entry_pointed() { return (_console_input->text_entry()->is_pointed()); }
};