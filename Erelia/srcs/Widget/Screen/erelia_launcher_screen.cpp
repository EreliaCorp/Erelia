#include "erelia.h"

void Launcher_screen::_on_geometry_change()
{
	button->set_geometry(100, jgl::Vector2Int(150, 50));
}

Launcher_screen::Launcher_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	button = new jgl::Button([&](jgl::Data_contener& p_param) {
			Publisher::instance()->notify(Main_application::Event::Go_world);
		}, this);
	button->label().set_text("Go world");
	button->activate();
}
	
void Launcher_screen::focus()
{

}
	
void Launcher_screen::unfocus()
{

}