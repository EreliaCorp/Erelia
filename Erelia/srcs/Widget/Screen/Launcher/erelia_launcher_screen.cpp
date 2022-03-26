#include "erelia.h"

void Launcher_screen::_on_geometry_change()
{
	jgl::Vector2 unit = _area / jgl::Vector2(86, 64);

	_menu->set_geometry(jgl::Vector2(1, 1) * unit, jgl::Vector2(43, 40) * unit);

	_registration_manager->set_geometry(jgl::Vector2(1, 42) * unit, jgl::Vector2(21, 5) * unit);
	_connection_manager->set_geometry(jgl::Vector2(23, 42) * unit, jgl::Vector2(21, 5) * unit);

	_message_output->set_geometry(jgl::Vector2(45, 1) * unit, jgl::Vector2(40, 62) * unit);
}

void Launcher_screen::set_text(jgl::String p_text_a, jgl::String p_text_b, jgl::String p_text_c)
{
	_message_output->set_text(p_text_a, p_text_b, p_text_c);
}

Launcher_screen::Launcher_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	Publisher::instanciate();

	_menu = new Launcher::Menu(this);
	_menu->activate();

	_registration_manager = new Registration_manager(this);
	_registration_manager->activate();

	_connection_manager = new Connection_manager(this);
	_connection_manager->activate();

	_message_output = new Launcher::Message_output(this);
	_message_output->activate();

}

void Launcher_screen::focus()
{

}
	
void Launcher_screen::unfocus()
{

}