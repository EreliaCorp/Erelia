#include "erelia.h"

namespace Routine
{
	void treat_command_input(Connection* p_client, Message& p_msg)
	{
		jgl::String message;

		p_msg >> message;

		Console_manager::instance()->console_parser()->add_command(message, p_client);
	}

	void receive_console_message(Message& p_msg)
	{
		jgl::String message;

		p_msg >> message;

		jgl::cout << "String receive : " << message << jgl::endl;

		Console_manager::instance()->console_output()->add_message(message);
	}
}