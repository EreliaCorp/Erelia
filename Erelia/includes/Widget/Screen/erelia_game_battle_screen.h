#pragma once

#include "widget/Abstract_widget/erelia_abstract_screen.h"

class Game_battle_screen : public Abstract_screen
{
private:
	jgl::Button* button;
	void _on_geometry_change();

public:
	Game_battle_screen(jgl::Widget* p_parent);
	void focus();
	void unfocus();
};