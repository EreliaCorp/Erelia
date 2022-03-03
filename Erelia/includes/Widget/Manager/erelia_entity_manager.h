#pragma once

#include "jgl.h"
#include "Enum/erelia_enum.h"

#include "Widget/Commun/erelia_entity_renderer.h"

class Entity_manager : public jgl::Widget
{
private:
	static Entity_manager* _instance;

	jgl::Array<jgl::Widget*> _widgets;

	void _on_geometry_change();
	void _render();
	void _change_connection_mode(Connection_mode p_mode);
	void _load_ui_file();
	Entity_manager(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);

public:
	static Entity_manager* instanciate(Connection_mode p_mode, jgl::Widget* p_parent = nullptr);
	static Entity_manager* instance();
};