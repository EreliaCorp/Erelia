#include "erelia.h"

void Loading_screen::_on_geometry_change()
{

}

Loading_screen::Loading_screen(jgl::Widget* p_parent) : Abstract_screen(p_parent)
{

}

void Loading_screen::focus()
{
	THROW_INFORMATION("Focus on loading screen");
}

void Loading_screen::unfocus()
{
	THROW_INFORMATION("Unfocus on loading screen");
}