#pragma once

#include "jgl.h"

class Player_info_menu : public jgl::Widget
{
private:
	jgl::Text_label* _username_label;
	jgl::Text_entry* _username_entry;
	jgl::Text_label* _password_label;
	jgl::Text_entry* _password_entry;

	void _on_geometry_change();
	void _render();

public:
	Player_info_menu(jgl::Widget* p_parent);
	void start();
	jgl::String username();
	jgl::String password();
};
