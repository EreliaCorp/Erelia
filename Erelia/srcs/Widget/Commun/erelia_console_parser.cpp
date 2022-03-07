#include "erelia.h"

void Console_parser::_parse_command(Command& p_command)
{
	if (p_command.text == "")
		return;
	else if (p_command.text[0] != '/')
	{
		Account* tmp_account = Account_atlas::instance()->active_account(p_command.sender->id());
		jgl::String account_name = "Error";
		
		if (tmp_account != nullptr)
			account_name = tmp_account->username;

		_send_global_message("[" + account_name + "] : " + p_command.text);
	}
	else
	{
		static jgl::Array<jgl::String> tab;
		p_command.text.split(tab, " ", true);
		if (tab[0] == "/gamemode")
		{
			if (tab.size() == 2 && (tab[1] == "Adventure" || tab[1] == "Builder"))
			{
				if (tab[1] == "Adventure")
				{
					_send_gamemode_modification(p_command.sender, Gamemode::Adventure);
					//Game_screen::instance()->set_gamemode(Gamemode::Adventure);
					_send_private_message("[Systm.] : Gamemode set to Adventure", p_command.sender);
				}
				else if (tab[1] == "Builder")
				{
					_send_gamemode_modification(p_command.sender, Gamemode::Builder);
					//Game_screen::instance()->set_gamemode(Gamemode::Builder);
					_send_private_message("[Systm.] : Gamemode set to Builder", p_command.sender);
				}
			}
			else
			{
				_send_private_message("[Systm.] : Usage \"/gamemode [Adventure / Builder]\"", p_command.sender);
			}
		}
		if (tab[0] == "/ping")
		{
			Client_manager::instance()->send_ping_request();
		}
		else
		{
			_send_private_message("[Systm.] : Command unknow [" + p_command.text + "]", p_command.sender);
		}
	}
}

Console_parser::Console_parser(Console_output* p_output, jgl::Widget* p_parent) : Abstract_console_parser(p_output, p_parent)
{

}