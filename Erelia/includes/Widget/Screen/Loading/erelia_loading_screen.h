#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Loading_screen : public Abstract_screen
{
private:
	void _on_geometry_change();

public:
	Loading_screen(jgl::Widget* p_parent);
	void focus();
	void unfocus();
};