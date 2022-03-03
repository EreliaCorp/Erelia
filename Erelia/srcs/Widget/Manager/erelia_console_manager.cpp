#include "erelia.h"

Console_manager* Console_manager::_instance = nullptr;

void Console_manager::_on_geometry_change()
{
	jgl::Vector2Int frame_size = jgl::Vector2Int(_area.x / 5 * 2, _area.y / 3);
	jgl::Vector2Int entry_size = jgl::Vector2Int(frame_size.x, frame_size.y / 8);
	if (entry_size.y < 35)
		entry_size.y = 35;

	if (_console_output != nullptr)
		_console_output->set_geometry(jgl::Vector2Int(0, _area.y - entry_size.y - frame_size.y), frame_size);
	if (_console_input != nullptr)
		_console_input->set_geometry(jgl::Vector2Int(0, _area.y - entry_size.y), entry_size);

	if (_console_parser != nullptr)
		_console_parser->set_geometry(0, _area);
}

void Console_manager::_render()
{

}

jgl::Bool Console_manager::_update()
{
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Return) == jgl::Input_status::Release)
	{
		if (_console_input->is_selected() == true)
		{
			_console_parser->add_command(_console_input->text());
			_console_input->reset_text();
		}
		else
		{
			_console_input->text_entry()->select();
		}
	}
	if (jgl::Application::active_application()->keyboard().get_key(jgl::Key::Escape) == jgl::Input_status::Release && _console_input->is_selected() == true)
		_console_input->text_entry()->unselect();
	return (false);
}

void Console_manager::_change_connection_mode(Connection_mode p_mode)
{
	_console_output = new Console_output(this);
	_console_output->set_depth(_depth + 100);
	_console_output->activate();
	_console_input = new Console_input(this);
	_console_input->set_depth(_depth + 100);
	_console_input->activate();

	if (p_mode == Connection_mode::Singleplayer)
	{
		_console_parser = new Singleplayer::Console_parser(_console_output, this);
	}
	else if (p_mode == Connection_mode::Multiplayer)
	{

	}
	else if (p_mode == Connection_mode::Host)
	{

	}
	if( _console_parser != nullptr)
		_console_parser->activate();
}

void Console_manager::_load_ui_file()
{

}

Console_manager::Console_manager(Connection_mode p_mode, jgl::Widget* p_parent) : jgl::Widget(p_parent)
{
	_load_ui_file();
	_change_connection_mode(p_mode);
}

Console_manager* Console_manager::instanciate(Connection_mode p_mode, jgl::Widget* p_parent)
{
	if (_instance == nullptr)
	{
		_instance = new Console_manager(p_mode, p_parent);
	}
	return (_instance);
}

Console_manager* Console_manager::instance()
{
	return (_instance);
}