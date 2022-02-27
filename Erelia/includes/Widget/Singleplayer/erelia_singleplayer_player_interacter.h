#pragma once

#include "jgl.h"

#include "Widget/Commun/erelia_graphical_widget.h"

namespace Singleplayer
{
	class Player_interacter : public Graphical_widget
	{
	private:
		void _render();
		void _on_geometry_change();

		jgl::Bool _update();

	public:
		Player_interacter(jgl::Widget* p_parent);
	};
}