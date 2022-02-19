#pragma once

#include "jgl.h"
#include "Enum/erelia_enum.h"

class Map_manager : public jgl::Widget
{
private:
	static Map_manager* _instance;

	jgl::Array<jgl::Widget*> _widgets;

	void _on_geometry_change();
	void _render();
	void _change_connection_mode(Connection_mode p_mode);
	void _load_ui_file();
	Map_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

public:
	static Map_manager* instanciate(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);
	static Map_manager* instance();
};