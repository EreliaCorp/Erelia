#include "erelia.h"

namespace Singleplayer
{
	void Console_parser::_parse_command(jgl::String& p_text)
	{
		if (p_text == "")
			return;
		else if (p_text[0] != '/')
			_output->add_message("[Player] : " + p_text);
		else
		{
			_output->add_message("[Systm.] : " + p_text);
		}
	}

	Console_parser::Console_parser(Console_output* p_output, jgl::Widget* p_parent) : Abstract_console_parser(p_output, p_parent)
	{

	}
}