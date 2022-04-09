#include "erelia.h"

Abstract_screen::Abstract_screen(jgl::Widget* p_parent) : jgl::Widget(p_parent)
{

}

void Abstract_screen::_render()
{

}

jgl::Bool Abstract_screen::_update()
{
	return (false);
}

jgl::Bool Abstract_screen::_fixed_update()
{
	return (false);
}