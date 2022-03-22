#include "erelia.h"

void Loading_screen::_on_geometry_change()
{
	button->set_geometry(100, jgl::Vector2Int(150, 50));
}

Loading_screen::Loading_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{
	button = new jgl::Button([&](jgl::Data_contener& p_param) {
		jgl::cout << "Loading screen button" << jgl::endl;
		}, this);
	button->label().set_text("Go world");
	button->activate();
}

void Loading_screen::focus()
{

}

void Loading_screen::unfocus()
{

}