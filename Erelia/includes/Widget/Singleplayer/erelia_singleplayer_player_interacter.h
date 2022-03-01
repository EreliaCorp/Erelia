#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_graphical_widget.h"
#include "Widget/Commun/erelia_editor_inventory.h"

namespace Singleplayer
{
	class Player_interacter : public Graphical_widget
	{
	private:
		Editor_inventory* _editor_inventory;

		void _render();
		void _on_geometry_change();

		jgl::Bool _update();
		void _activate_editor_inventory();
		void _desactivate_editor_inventory();

	public:
		Player_interacter(jgl::Widget* p_parent);
	};
}