#pragma once

#include "Widget/Commun/erelia_graphical_widget.h"

namespace Singleplayer
{
	class Map_loader : public Graphical_widget
	{
	private:
		void _on_geometry_change();
		void _render();

		jgl::Bool _update();

	public:
		Map_loader(jgl::Widget* p_parent = nullptr);
	};
};