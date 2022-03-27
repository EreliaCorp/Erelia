#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Loading_screen : public Abstract_screen, public jgl::Singleton_widget<Loading_screen>
{
	friend class  jgl::Singleton_widget<Loading_screen>;

private:
	void _on_geometry_change();

	Loading_screen(jgl::Widget* p_parent);

public:
	void focus();
	void unfocus();
};