#pragma once

#include "jgl.h"

#include "widget/Commun/erelia_slider_widget.h"

class NPC_creator_interface : public jgl::Widget
{
private:
	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	Slider* _slider;

	jgl::Button* _slider_button;
	jgl::Frame* _frame;

public:
	NPC_creator_interface(jgl::Widget* p_parent);
};