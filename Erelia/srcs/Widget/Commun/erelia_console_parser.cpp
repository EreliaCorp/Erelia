#include "erelia.h"


jgl::String Console_parser::_parse_block_composition(jgl::String p_entry)
{
	jgl::String result = "";

	static jgl::Array<jgl::String> tab;
	static jgl::Array<jgl::String> sub_tab;

	p_entry.split(tab, ",");

	for (jgl::Size_t i = 0; i < tab.size(); i++)
	{
		tab[i].split(sub_tab, "%");

		if (sub_tab.size() == 1)
		{
			if (sub_tab[0].compose_only("0123456789.") == false || sub_tab[0].compose_only(".") == true)
				return ("");
			else
				result += (result != "" ? jgl::String("/") : jgl::String()) + "100/" + sub_tab[0];
		}
		else if (sub_tab.size() == 2)
		{
			if (sub_tab[0].compose_only("0123456789.") == false || sub_tab[0].compose_only(".") == true || sub_tab[1].compose_only("0123456789.") == false || sub_tab[1].compose_only(".") == true)
				return ("");
			else
				result += (result != "" ? jgl::String("/") : jgl::String()) + sub_tab[0] + "/" + sub_tab[1];
		}
		else
		{
			return ("");
		}
	}

	return (result);
}

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
					_send_private_message("[Systm.] : Gamemode set to Adventure", p_command.sender);
				}
				else if (tab[1] == "Builder")
				{
					_send_gamemode_modification(p_command.sender, Gamemode::Builder);
					_send_private_message("[Systm.] : Gamemode set to Builder", p_command.sender);
				}
			}
			else
			{
				_send_private_message("[Systm.] : Usage \"/gamemode [Adventure / Builder]\"", p_command.sender);
			}
		}
		else if (tab[0] == "/ping")
		{
			Client_manager::instance()->send_ping_request();
		}
		else if (tab[0] == "/brush_size")
		{
			jgl::Int value = -1;

			if (tab.size() == 2)
				value = jgl::stoi(tab[1]);
			
			if(value >= 0 && value <= 16)
			{
				_send_brush_size_modification(p_command.sender, value);
				_send_private_message("[Systm.] : Brush size set to " + jgl::itoa(value), p_command.sender);
			}
			else
				_send_private_message("[Systm.] : Usage \"/brush_size [Radius size from 0 to 16]\"", p_command.sender);
		}
		else if (tab[0] == "/replace")
		{
			if (tab.size() == 3)
			{
				jgl::String block_entry = _parse_block_composition(tab[1]);
				jgl::String block_output = _parse_block_composition(tab[2]);

				if (block_entry != "" && block_entry.compose_only("1234567890/.") == true && block_output != "")
				{
					_send_brush_type_data(p_command.sender, block_entry + " " + block_output);
					_send_brush_type_modification(p_command.sender, Player_interacter::Brush_type::Brush_replace);
					_send_private_message("[Systm.] : Replace tiles [" + block_entry + "] with [" + block_output + "]\"", p_command.sender);
				}
				else
				{
					_send_private_message("[Systm.] : Usage \"/replace [Unique tile type to change] [tile to place]\"", p_command.sender);
					_send_private_message("[Systm.] :       \"/replace [off] to disable replace mode\"", p_command.sender);
				}
			}
			else if (tab.size() == 2 && tab[1] == "off")
			{
				_send_brush_type_modification(p_command.sender, Player_interacter::Brush_type::Brush_place);
				_send_private_message("[Systm.] : Replace mode disable", p_command.sender);
			}
			else
			{
				_send_private_message("[Systm.] : Usage \"/replace [Unique tile type to change] [tile to place]\"", p_command.sender);
				_send_private_message("[Systm.] :       \"/replace [off] to disable replace mode\"", p_command.sender);
			}
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