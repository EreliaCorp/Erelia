#pragma once

#include "Widget/Commun/erelia_graphical_widget.h"

namespace Singleplayer
{
	class Player_updater : public Graphical_widget
	{
	private:
		void _on_geometry_change();
		void _render();

		jgl::Bool _update();

	public:
		Player_updater(jgl::Widget* p_parent = nullptr);
	};
}