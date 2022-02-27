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
			static jgl::Array<jgl::String> tab;
			p_text.split(tab, " ", true);
			if (tab[0] == "/gamemode")
			{
				if (tab.size() == 2 && (tab[1] == "Adventure" || tab[1] == "Builder"))
				{
					if (tab[1] == "Adventure")
					{
						Game_manager::instance()->set_gamemode(Gamemode::Adventure);
						_output->add_message("[Systm.] : Gamemode set to Adventure");
					}
					else if (tab[1] == "Builder")
					{
						Game_manager::instance()->set_gamemode(Gamemode::Builder);
						_output->add_message("[Systm.] : Gamemode set to Builder");
					}
				}
				else
				{
					_output->add_message("[Systm.] : Usage \"/gamemode [Adventure / Builder]\"");
				}
			}
			else
			{
				_output->add_message("[Systm.] : Command unknow [" + p_text + "]");
			}
		}
	}

	Console_parser::Console_parser(Console_output* p_output, jgl::Widget* p_parent) : Abstract_console_parser(p_output, p_parent)
	{

	}
}