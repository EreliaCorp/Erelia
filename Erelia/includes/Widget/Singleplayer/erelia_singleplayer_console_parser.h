#pragma once

#include "Widget/Commun/erelia_abstract_console_parser.h"
#include "Widget/Commun/erelia_console_output.h"

namespace Singleplayer
{
	class Console_parser : public Abstract_console_parser
	{
	private:
		virtual void _parse_command(jgl::String& p_text);

	public:
		Console_parser(Console_output* p_output, jgl::Widget* p_parent);
	};
}