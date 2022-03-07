#pragma once

#include "Widget/Commun/erelia_graphical_widget.h"

class Map_loader : public Graphical_widget
{
private:
	jgl::Map<jgl::Vector2Int, jgl::Bool> _asked_chunks;
	jgl::Array<jgl::Vector2Int> _asked_chunk_list;

	void _on_geometry_change();
	void _render();

	jgl::Bool _update();

	void _request_chunk_data();

public:
	Map_loader(jgl::Widget* p_parent = nullptr);
};